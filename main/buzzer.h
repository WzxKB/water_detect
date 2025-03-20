#include "driver/ledc.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class Buzzer
{
public:
    // 单例获取接口
    static Buzzer &GetInstance()
    {
        static Buzzer instance; // 静态局部变量保证线程安全（C++11特性）
        return instance;
    }

    // 删除拷贝构造和赋值运算符
    Buzzer(const Buzzer &) = delete;
    Buzzer &operator=(const Buzzer &) = delete;

    // 初始化硬件配置
    void Init()
    {
        ledc_timer_config_t timerConfig = {
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .duty_resolution = LEDC_TIMER_8_BIT,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = 2000, // 2kHz频率
            .clk_cfg = LEDC_AUTO_CLK};
        ledc_timer_config(&timerConfig);

        ledc_channel_config_t channelConfig = {
            .gpio_num = GPIO_NUM_2, // 蜂鸣器连接IO2
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel = LEDC_CHANNEL_0,
            .timer_sel = LEDC_TIMER_0,
            .duty = 0, // 初始占空比为0
            .hpoint = 0};
        ledc_channel_config(&channelConfig);
    }

    // 控制蜂鸣器开关
    void Set(bool enable)
    {
        if (enable)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 128); // 50%占空比
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        }
        else
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        }
    }

private:
    // 私有构造函数和析构函数
    Buzzer() = default; // 初始化逻辑通过Init方法暴露
    ~Buzzer()
    {
        Set(false); // 确保销毁时关闭蜂鸣器
    }
};
