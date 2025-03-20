#pragma once
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include <mutex>

#define WATER_DETEC_START_VALUE 100.00 // 刚放入水中的模拟值
#define WATER_DETEC_END_VALUE 1500.00
#define WATER_DETEC_LEN 40.00 // 检测的传感器的长度
#define WATER_DETEC_PART ((WATER_DETEC_END_VALUE - WATER_DETEC_START_VALUE) / WATER_DETEC_LEN)
class BoardAdc
{
public:
    static BoardAdc &GetInstance()
    {
        static BoardAdc instance;
        return instance;
    }

    BoardAdc(const BoardAdc &) = delete;
    BoardAdc &operator=(const BoardAdc &) = delete;

    void Init(adc_channel_t channel = ADC_CHANNEL_0,
              adc_atten_t atten = ADC_ATTEN_DB_12,
              adc_bitwidth_t bitwidth = ADC_BITWIDTH_12);
    int Read(bool convert);
    int Covert(int adc_value);
    void Deinit();

private:
    BoardAdc() = default;
    ~BoardAdc() = default;

    static bool AdcCalibrationInit(adc_unit_t unit,
                                   adc_channel_t channel,
                                   adc_atten_t atten,
                                   adc_bitwidth_t bitwidth,
                                   adc_cali_handle_t *cali_handle);

    std::mutex adc_mutex_;
    bool calibrated_ = false;
    adc_oneshot_unit_handle_t oneshot_handle_ = nullptr;
    adc_cali_handle_t cali_handle_ = nullptr;
    adc_channel_t channel_ = ADC_CHANNEL_1;
};