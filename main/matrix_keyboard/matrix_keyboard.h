#pragma once
#include "keyboard_button.h"
#include "esp_log.h"
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <array>
#include <mutex>

class MatrixKeyboard
{
public:
    // 单例访问接口
    static MatrixKeyboard &getInstance()
    {
        static MatrixKeyboard instance;
        return instance;
    }

    // 初始化函数
    bool Init(keyboard_btn_config_t cfg);

    // 注册回调函数
    void registerCb(keyboard_btn_cb_config_t &cb_cfg);

    // 获取队列
    QueueHandle_t getQueue() const { return queue_; }

private:
    // 私有构造函数
    MatrixKeyboard() : m_kbd_handle(nullptr), m_kdb_cb_handle(nullptr), queue_(nullptr) {}
    ~MatrixKeyboard();

    // 禁用拷贝构造和赋值
    MatrixKeyboard(const MatrixKeyboard &) = delete;
    MatrixKeyboard &operator=(const MatrixKeyboard &) = delete;

    // 静态回调函数
    static void keyboard_cb(keyboard_btn_handle_t kbd_handle,
                            keyboard_btn_report_t kbd_report,
                            void *user_data);

    // 成员变量
    keyboard_btn_handle_t m_kbd_handle;
    keyboard_btn_cb_handle_t m_kdb_cb_handle;
    QueueHandle_t queue_;
};