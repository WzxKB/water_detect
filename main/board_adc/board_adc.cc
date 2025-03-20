#include "board_adc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define TAG "ADC"
#define SAMPLE_TIMES 16 // 多次采样降低噪声

bool BoardAdc::AdcCalibrationInit(adc_unit_t unit,
                                  adc_channel_t channel,
                                  adc_atten_t atten,
                                  adc_bitwidth_t bitwidth,
                                  adc_cali_handle_t *cali_handle)
{
    esp_err_t ret = ESP_FAIL;
    bool calibrated = false;

    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = unit,
        .chan = channel, // 修正字段名[3](@ref)
        .atten = atten,
        .bitwidth = bitwidth};

    ret = adc_cali_create_scheme_curve_fitting(&cali_config, cali_handle);
    if (ret == ESP_OK)
    {
        calibrated = true;
        ESP_LOGI(TAG, "Calibration scheme initialized");
    }
    else if (ret == ESP_ERR_NOT_SUPPORTED)
    {
        ESP_LOGW(TAG, "Skip software calibration");
    }
    else
    {
        ESP_LOGE(TAG, "Calibration failed: 0x%x", ret);
    }
    return calibrated;
}

void BoardAdc::Init(adc_channel_t channel,
                    adc_atten_t atten,
                    adc_bitwidth_t bitwidth)
{
    std::lock_guard<std::mutex> lock(adc_mutex_);

    adc_unit_t unit = ADC_UNIT_1;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit,
        .ulp_mode = ADC_ULP_MODE_DISABLE};

    // 初始化ADC单元
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &oneshot_handle_));

    // 配置ADC通道
    adc_oneshot_chan_cfg_t chan_config = {
        .atten = atten,
        .bitwidth = bitwidth,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(oneshot_handle_, channel, &chan_config));

    // 初始化校准
    calibrated_ = AdcCalibrationInit(unit, channel, atten, bitwidth, &cali_handle_);
    channel_ = channel;

    ESP_LOGI(TAG, "ADC Unit%d Channel%d initialized", unit + 1, channel);
}

int BoardAdc::Read(bool convert)
{
    std::lock_guard<std::mutex> lock(adc_mutex_);
    int adc_sum = 0;

    // 多次采样取平均[5](@ref)
    for (int i = 0; i < SAMPLE_TIMES; i++)
    {
        int single_value = 0;
        esp_err_t ret = adc_oneshot_read(oneshot_handle_, channel_, &single_value);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Read failed: 0x%x", ret);
            return -1;
        }
        adc_sum += single_value;
    }
    int adc_value = adc_sum / SAMPLE_TIMES;

    if (calibrated_ && convert)
    {
        int voltage = 0;
        esp_err_t ret = adc_cali_raw_to_voltage(cali_handle_, adc_value, &voltage);
        if (ret == ESP_OK)
        {
            return voltage; // 返回校准后的电压值(mV)
        }
    }
    return adc_value; // 返回原始ADC值或错误值
}

int BoardAdc::Covert(int adc_value)
{
    constexpr double value = static_cast<double>(WATER_DETEC_PART);
    return static_cast<int>((adc_value - WATER_DETEC_START_VALUE) / value);
}

void BoardAdc::Deinit()
{
    std::lock_guard<std::mutex> lock(adc_mutex_);

    if (cali_handle_)
    {
        adc_cali_delete_scheme_curve_fitting(cali_handle_);
    }
    if (oneshot_handle_)
    {
        adc_oneshot_del_unit(oneshot_handle_);
    }
    ESP_LOGI(TAG, "ADC resources released");
}