#pragma once
#include "keyboard_button.h"
#include "esp_log.h"
#ifdef __cplusplus
extern "C"
{
#endif
    void matriKeybord_init(void);
    namespace wd
    {

        class matrixKeyboard
        {
        private:
            keyboard_btn_config_t m_cfg;
            keyboard_btn_handle_t m_kbd_handle = nullptr;
            keyboard_btn_cb_handle_t m_kdb_cb_handle = nullptr;

        public:
            matrixKeyboard(const keyboard_btn_config_t &cfg) : m_cfg(cfg)
            {
                // 通过构造函数初始化列表直接初始化成员变量
                // 通过构造函数初始化列表直接初始化成员变量
                if (keyboard_button_create(&m_cfg, &m_kbd_handle) != ESP_OK)
                {
                    ESP_LOGE("matrixKeyboard", "Failed to initialize keyboard");
                }
                else
                {
                    ESP_LOGI("matrixKeyboard", "matrixKeyboard init success");
                }
            }
            ~matrixKeyboard()
            {
                // 销毁资源，比如释放 m_kbd_handle 和 m_kdb_cb_handle
                if (m_kbd_handle != nullptr)
                {
                    keyboard_button_delete(m_kbd_handle);
                }
            }
            void register_cb(keyboard_btn_cb_config_t &cb_cfg);
        };
    }

#ifdef __cplusplus
}
#endif