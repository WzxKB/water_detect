#include "ui.h"

void Ui::Init(lv_ui *uis)
{
    ui_ = std::move(uis);
}

// 设置显示当前水位值
void Ui::SetCurrentValue(int32_t value)
{
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->display_screen)
    {
        lv_label_set_text_fmt(ui_->display_screen_current_value, "%ld", value);
    }
    this->UnLock();
}

// 获取显示报警水位值
void Ui::GetAlarmValue()
{
    int32_t water_level = 0;
    this->GetWaterValue(&water_level);
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->display_screen)
    {
        lv_label_set_text_fmt(ui_->display_screen_alarm_value, "%ld", water_level);
    }
    this->UnLock();
}

// 获取显示设置水位值
void Ui::GetConfigValue()
{
    int32_t water_level = 0;
    this->GetWaterValue(&water_level);
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->config_screen)
    {
        lv_label_set_text_fmt(ui_->config_screen_config_value, "%ld", water_level);
    }
    this->UnLock();
}

esp_err_t Ui::SaveWaterValue(int32_t water_level)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open NVS namespace: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_set_i32(nvs_handle, "water_level", water_level);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to save water level: %s", esp_err_to_name(ret));
        nvs_close(nvs_handle);
        return ret;
    }

    ret = nvs_commit(nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to commit NVS changes: %s", esp_err_to_name(ret));
    }

    nvs_close(nvs_handle);
    return ret;
}

esp_err_t Ui::GetWaterValue(int32_t *water_level)
{
    nvs_handle_t nvs_handle;
    esp_err_t ret = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open NVS namespace: %s", esp_err_to_name(ret));
        return ret;
    }

    ret = nvs_get_i32(nvs_handle, "water_level", water_level);
    if (ret == ESP_ERR_NVS_NOT_FOUND)
    {
        *water_level = 0;
        ret = nvs_set_i32(nvs_handle, "water_level", *water_level);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to set default water level: %s", esp_err_to_name(ret));
            nvs_close(nvs_handle);
            return ret;
        }

        ret = nvs_commit(nvs_handle);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to commit default water level: %s", esp_err_to_name(ret));
        }
        ESP_LOGI(TAG, "Default water level 0 set and saved to NVS");
    }
    else if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get water level: %s", esp_err_to_name(ret));
    }

    nvs_close(nvs_handle);
    return ret;
}

void Ui::NextScreen()
{
    this->Lock(LockTime);
    static int current_screen_index = 0;
    std::array<lv_obj_t *, 3> screen_array = {ui_->cover_screen, ui_->config_screen, ui_->display_screen};
    int screen_count = screen_array.size();
    current_screen_index = (current_screen_index + 1) % screen_count;
    auto screen = screen_array[current_screen_index];
    lv_scr_load(screen);
    this->GetAlarmValue();
    this->GetConfigValue();
    this->UnLock();
}
// 设置并写入报警水位,并显示在页面
void Ui::SetConfigvalue(int32_t value)
{
    this->SaveWaterValue(value);
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->config_screen)
    {
        lv_label_set_text_fmt(ui_->config_screen_config_value, "%ld", value);
    }
    this->UnLock();
}

// 按*键开始设置，label变成 _
void Ui::SetConfigvalueStart()
{
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->config_screen)
    {
        lv_label_set_text_fmt(ui_->config_screen_config_value, "_");
    }
    this->UnLock();
}
// 设置的时候显示的数据
void Ui::SetConfigvalueDuring(std::string label)
{
    this->Lock(LockTime);
    if (lv_scr_act() == ui_->config_screen)
    {
        lv_label_set_text_fmt(ui_->config_screen_config_value, "%s", label.c_str());
    }
    this->UnLock();
}

bool Ui::Lock(int timeout_ms)
{
    return lvgl_port_lock(timeout_ms);
}

void Ui::UnLock()
{
    lvgl_port_unlock();
}