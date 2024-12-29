#include <stdio.h>
#include "matrixKeyboard.h"
#include "string"
#include "array"
#include "iostream"
#include "gui_guider.h"
#include "lvgl.h"
#include "esp_lvgl_port.h"
SemaphoreHandle_t lvgl_mutex; // 声明互斥锁
static const char *TAG = "matrixKeyboard";

static bool allow_set_digit = false;
static std::string digit = "";

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
        lvgl_port_lock(0);
        if (xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        {
            switch (str[0])
            {
            case '1':

            case '2':

            case '3':

            case '4':

            case '5':

            case '6':

            case '7':

            case '8':

            case '9':

            case '0':
                if (allow_set_digit == true && lv_scr_act() == guider_ui.screen_1)
                {
                    digit += str;
                    lv_label_set_text(guider_ui.screen_1_label_2, digit.c_str()); // 设置标签文本
                    lv_obj_set_style_text_color(guider_ui.screen_1_label_2, lv_color_hex(0x000000), 0);
                }

                break;
            case 'A':
                /* code */
                do
                {
                    lv_obj_t *screen = lv_scr_act();

                    if (guider_ui.screen == screen)
                    {
                        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);

                        printf("A11\n");
                    }
                    else if (guider_ui.screen_1 == screen)
                    {
                        ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_1_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
                        printf("A22\n");
                    }
                    else if (guider_ui.screen_2 == screen)
                    {
                        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_2_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);

                        printf("A33\n");
                    }
                } while (0);
                break;
            case 'B':
                /* code */

                break;
            case 'C':
                /* code */
                break;
            case 'D':
                /* code */
                break;
            case '*':
                /* code */
                if (lv_scr_act() == guider_ui.screen_1)
                {
                    digit.clear();
                   
                    allow_set_digit = true;

                    lv_label_set_text(guider_ui.screen_1_label_2, "_"); // 设置标签文本
                    lv_obj_set_style_text_color(guider_ui.screen_1_label_2, lv_color_hex(0x000000), 0);
                }

                break;
            case '#':
                /* code */
                do
                {
                    if (lv_scr_act() == guider_ui.screen_1)
                    {
                        static lv_style_t label_style;

                        allow_set_digit = false;
                        lv_label_set_text(guider_ui.screen_1_label_2, digit.c_str());  // 设置标签文本
                        lv_obj_set_style_text_color(guider_ui.screen_1_label_2, lv_color_hex(0xff0000), 0);

                    }
                } while (0);

                break;
            default:
                break;
            }

            xSemaphoreGive(lvgl_mutex); // 解锁
        }
        lvgl_port_unlock();
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
    lvgl_mutex = xSemaphoreCreateMutex();        // 创建互斥锁
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