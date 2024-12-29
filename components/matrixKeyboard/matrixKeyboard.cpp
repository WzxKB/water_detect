#include <stdio.h>
#include "matrixKeyboard.h"
#include "string"
#include "array"
#include "iostream"

static const char *TAG = "matrixKeyboard";

// 定义一个函数返回二维数组中的某个字符串元素
static std::string getKeyItem(const std::array<std::array<std::string, 4>, 4> &key_arr, int row, int col)
{
    if (row < 0 || row >= 4 || col < 0 || col >= 4)
    {
        throw std::out_of_range("Index out of range");
    }
    return key_arr[col][row];
}

static std::string key_map_string(int output_index, int input_index)
{
    std::array<std::array<std::string, 4>, 4> key_arr =
        {{
            {"1", "2", "3", "A"},
            {"4", "5", "6", "B"},
            {"7", "8", "9", "C"},
            {"*", "0", "#", "D"},

        }};
    return getKeyItem(key_arr, output_index, input_index);
}

static void
keyboard_cb(keyboard_btn_handle_t kbd_handle, keyboard_btn_report_t kbd_report, void *user_data)
{

    if (kbd_report.key_pressed_num == 0)
    {
        ESP_LOGI(TAG, "All keys released\n\n");
        return;
    }

    printf("pressed: ");
    for (int i = 0; i < kbd_report.key_pressed_num; i++)
    {
        printf("(%d,%d) ", kbd_report.key_data[i].output_index, kbd_report.key_data[i].input_index);
        std::string str = key_map_string(kbd_report.key_data[i].output_index, kbd_report.key_data[i].input_index);
        std::cout << "Item: " << str << std::endl;
    }
    printf("\n\n");
}

void wd::matrixKeyboard::register_cb(keyboard_btn_cb_config_t &cb_cfg)
{
    // 注册回调
    if (m_kbd_handle != nullptr)
    {
        // 假设函数 register_cb 接受 m_kbd_handle 和 cb_cfg
        cb_cfg.callback = keyboard_cb;

        if (keyboard_button_register_cb(m_kbd_handle, cb_cfg, &m_kdb_cb_handle) != ESP_OK)
        {
            ESP_LOGE("matrixKeyboard", "Failed to register callback");
        }
        else
        {
            ESP_LOGI("matrixKeyboard", "Callback registered successfully");
        }
    }
    else
    {
        ESP_LOGE("matrixKeyboard", "Keyboard handle is not initialized");
    }
}

void matriKeybord_init(void)
{
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
    wd::matrixKeyboard *keyboard = new wd::matrixKeyboard(cfg);
    keyboard_btn_cb_config_t cb_cfg = {
        .event = KBD_EVENT_PRESSED,
    };
    if (keyboard != nullptr)
    {
        keyboard->register_cb(cb_cfg);
    }
}