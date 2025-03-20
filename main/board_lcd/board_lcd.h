
#pragma once
#ifdef __cplusplus
extern "C"
{
#endif
#define LCD_H_RES (240)
#define LCD_V_RES (240)
/* LCD settings */
#define LCD_SPI_NUM (SPI2_HOST)
#define LCD_PIXEL_CLK_HZ (80 * 1000 * 1000)
#define LCD_CMD_BITS (8)
#define LCD_PARAM_BITS (8)
#define LCD_COLOR_SPACE (ESP_LCD_COLOR_SPACE_BGR)
#define LCD_BITS_PER_PIXEL (16)
#define LCD_DRAW_BUFF_DOUBLE (1)
#define LCD_DRAW_BUFF_HEIGHT (50)
#define LCD_BL_ON_LEVEL (1)

    void _lcd_init(void);

#ifdef __cplusplus
}
#endif
