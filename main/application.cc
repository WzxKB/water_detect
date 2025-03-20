#include "application.h"
#include "matrix_keyboard.h"
#include "board_adc.h"
#include "ui.h"
#include "buzzer.h"
#include <esp_log.h>

// 定义构造函数
Application::Application()
{
    // 构造函数的实现
}

// 定义析构函数
Application::~Application()
{
    // 析构函数的实现
}

static void matrix_keyboard_init()
{
    /*初始化键盘*/
    const int output_gpios[4] = {9, 10, 11, 12}; // Declare fixed-size array
    const int input_gpios[4] = {13, 14, 21, 47};

    keyboard_btn_config_t cfg =
        {
            .output_gpios = output_gpios,
            .input_gpios = input_gpios,
            .output_gpio_num = 4,
            .input_gpio_num = 4,
            .active_level = 1,
            .debounce_ticks = 2,
            .ticks_interval = 500,      // us
            .enable_power_save = false, // enable power save
            .priority = 15,
            .core_id = 1,
        };
    auto &keyboard = MatrixKeyboard::getInstance();
    if (!keyboard.Init(cfg))
    {
        ESP_LOGE(TAG, "键盘初始化失败");
        esp_restart();
    }
    keyboard_btn_cb_config_t cb_cfg = {
        .event = KBD_EVENT_PRESSED,
    };

    keyboard.registerCb(cb_cfg);
}

void Application::Start(lv_ui *uis)
{
    // 初始化蜂鸣器
    auto &buzzer = Buzzer::GetInstance();
    buzzer.Init();
    // 初始化UI
    auto &ui = Ui::GetInstance();
    ui.Init(uis);
    // 初始化adc
    auto &boardAdc = BoardAdc::GetInstance();
    boardAdc.Init();
    // 初始化键盘
    matrix_keyboard_init();
    /* Start the main loop ,这个任务用来处理键盘事件*/
    xTaskCreate([](void *arg)
                {
        Application* app = (Application*)arg;
        app->MainLoop();
        vTaskDelete(NULL); }, "main_loop", 4096 * 2, this, 2, nullptr);
    /* Start the main loop ,这个任务用来处理键盘事件*/
    xTaskCreate([](void *arg)
                {
        Application* app = (Application*)arg;
        app->AdcDetectLoop();
        vTaskDelete(NULL); }, "adc_loop", 4096 * 2, this, 2, nullptr);
}

void Application::get_config_value_label(std::string &label, char la)
{
    label.push_back(la);
    int tmp = std::stoi(label);
    if (tmp > WATER_DETEC_LEN)
        label.clear();
}

void Application::AdcDetectLoop()
{
    auto &adc = BoardAdc::GetInstance();
    auto &ui = Ui::GetInstance();
    auto &buzzer = Buzzer::GetInstance();
    int32_t water_level = 0;
    ui.GetWaterValue(&water_level);
    while (true)
    {
        int adc_value = adc.Read(true);
        if (adc_value == -1)
        {
            ESP_LOGE(TAG, "adc 检测出错!");
        }
        int covert_value = 0;
        if (adc_value != 0)
        {
            covert_value = adc.Covert(adc_value);
        }

        ui.SetCurrentValue(covert_value);
        ESP_LOGI(TAG, "adc_vale:%d covert_value:%d", adc_value, covert_value);
        if (adc_value > water_level)
        {
            buzzer.Set(true);
            // 蜂鸣器叫
            ESP_LOGE(TAG, "蜂鸣器叫");
        }
        else
        {
            buzzer.Set(false);
            // 蜂鸣器不叫
            ESP_LOGE(TAG, "蜂鸣器不叫");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// 这个主循环检测键盘改变屏幕的事件
void Application::MainLoop()
{
    QueueHandle_t queue = MatrixKeyboard::getInstance().getQueue();
    char key;
    auto &ui = Ui::GetInstance();
    std::string cofig_label;
    while (true)
    {
        if (xQueueReceive(queue, &key, portMAX_DELAY) == pdTRUE)
        {
            switch (key)
            {
            // D 下一页
            case 'D':
                ESP_LOGI(TAG, "切换下一页");
                ui.NextScreen();
                break;
            case '*':
                ESP_LOGI(TAG, "开始写入水位阈值");
                ui.SetConfigvalueStart();
                cofig_label.clear();
                break;
            case '#':
                ESP_LOGI(TAG, "写入数据");
                ui.SetConfigvalue(std::stoi(cofig_label));
                cofig_label.clear();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                this->get_config_value_label(cofig_label, key);
                ui.SetConfigvalueDuring(cofig_label);
                break;
            default:
                ESP_LOGE(TAG, "不支持的按键");
            }
        }
    }
}
