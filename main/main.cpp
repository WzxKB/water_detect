

#include <iostream>
#include <memory> // 为智能指针添加支持
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "lvgl.h"
#include "custom.h"
#include "_lcd.h"
#include "gui_guider.h"
#include "matrixKeyboard.h"
lv_ui guider_ui;
#define DISP_BUF_SIZE 240 * 240
using namespace std;
#define LVGL_TICK_MS 1

void lv_tick_task(void *arg)
{
    lv_tick_inc(LVGL_TICK_MS);
}

extern "C" void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    matriKeybord_init();
    // /* Initialize SPI or I2C bus used by the drivers */
    // _lcd_init();
    // lv_init();
    // setup_ui(&guider_ui);

    // while (1)
    // {
    //     /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
    //     vTaskDelay(pdMS_TO_TICKS(10));
    //     lv_task_handler();
    // }
}
