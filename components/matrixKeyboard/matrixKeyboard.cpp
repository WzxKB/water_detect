#include <stdio.h>
#include "matrixKeyboard.h"

static const char *TAG = "matrixKeyboard";

static void keyboard_cb(keyboard_btn_handle_t kbd_handle, keyboard_btn_report_t kbd_report, void *user_data)
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