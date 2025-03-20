#ifndef UI_H
#define UI_H

#include "gui_guider.h"
#include "esp_err.h"
#include <lvgl.h>
#include <esp_lvgl_port.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include <array>
#include <string>

#define TAG "Ui"
#define LockTime 3000

class Ui
{
public:
    // 获取单例实例
    static Ui &GetInstance()
    {
        // 静态成员变量初始化
        static Ui instance;
        return instance;
    }

    // 初始化函数
    void Init(lv_ui *uis);

    void SetCurrentValue(int32_t value);

    void NextScreen();
    // 按*键开始设置，label变成 _
    void SetConfigvalueStart();
    // 设置的时候显示的数据
    void SetConfigvalueDuring(std::string label);
    void SetConfigvalue(int32_t value);
    esp_err_t GetWaterValue(int32_t *water_level);

private:
    // 私有构造函数，防止外部实例化
    Ui() = default;

    // 删除拷贝构造函数和赋值运算符
    Ui(const Ui &) = delete;
    Ui &operator=(const Ui &) = delete;
    void GetAlarmValue();
    void GetConfigValue();
    lv_ui *ui_;
    esp_err_t SaveWaterValue(int32_t water_level);
    bool Lock(int timeout_ms);
    void UnLock();
};

#endif // UI_H