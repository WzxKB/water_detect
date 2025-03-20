#include "matrix_keyboard.h"
#include <stdio.h>
#include <string>
#include <array>
#include <iostream>

static const char *TAG = "MatrixKeyboard";

// 获取二维数组中的某个字符元素
static char getKeyItem(const std::array<std::array<char, 4>, 4> &key_arr, int row, int col)
{
    if (row < 0 || row >= 4 || col < 0 || col >= 4)
    {
        throw std::out_of_range("Index out of range");
    }
    return key_arr[col][row];
}

// 按键映射函数
static char key_map_string(int output_index, int input_index)
{
    std::array<std::array<char, 4>, 4> key_arr = {{
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    }};
    return getKeyItem(key_arr, output_index, input_index);
}

// 初始化函数
bool MatrixKeyboard::Init(keyboard_btn_config_t cfg)
{
    if (m_kbd_handle != nullptr)
    {
        ESP_LOGE(TAG, "Keyboard already initialized");
        return false;
    }

    // 创建队列
    queue_ = xQueueCreate(10, sizeof(char));
    if (queue_ == nullptr)
    {
        ESP_LOGE(TAG, "Failed to create queue");
        return false;
    }

    // 初始化键盘
    if (keyboard_button_create(&cfg, &m_kbd_handle) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to initialize keyboard");
        vQueueDelete(queue_);
        return false;
    }

    ESP_LOGI(TAG, "Keyboard initialized successfully");
    return true;
}

// 析构函数
MatrixKeyboard::~MatrixKeyboard()
{
    if (m_kbd_handle)
    {
        keyboard_button_delete(m_kbd_handle);
    }
    if (queue_)
    {
        vQueueDelete(queue_);
    }
}

// 回调函数
void MatrixKeyboard::keyboard_cb(keyboard_btn_handle_t kbd_handle,
                                 keyboard_btn_report_t kbd_report,
                                 void *user_data)
{
    MatrixKeyboard *instance = static_cast<MatrixKeyboard *>(user_data);

    if (kbd_report.key_pressed_num == 0)
    {
        ESP_LOGI(TAG, "All keys released\n\n");
        return;
    }

    printf("pressed: ");
    for (int i = 0; i < kbd_report.key_pressed_num; i++)
    {
        printf("(%d,%d) ", kbd_report.key_data[i].output_index, kbd_report.key_data[i].input_index);
        char kc = key_map_string(kbd_report.key_data[i].output_index, kbd_report.key_data[i].input_index);
        std::cout << "Item: " << kc << std::endl;
        xQueueSend(instance->queue_, &kc, portMAX_DELAY);
    }
    printf("\n\n");
}

// 注册回调函数
void MatrixKeyboard::registerCb(keyboard_btn_cb_config_t &cb_cfg)
{
    if (m_kbd_handle != nullptr)
    {
        cb_cfg.callback = MatrixKeyboard::keyboard_cb;
        cb_cfg.user_data = this;

        if (keyboard_button_register_cb(m_kbd_handle, cb_cfg, &m_kdb_cb_handle) != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to register callback");
        }
        else
        {
            ESP_LOGI(TAG, "Callback registered successfully");
        }
    }
    else
    {
        ESP_LOGE(TAG, "Keyboard handle is not initialized");
    }
}