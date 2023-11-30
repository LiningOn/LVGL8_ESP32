/**
 * @file lvgl_helpers.h
 */

#ifndef LVGL_HELPERS_H
#define LVGL_HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdbool.h>

#include "lvgl_spi_conf.h"
#include "lvgl_tft/disp_driver.h"
#include "lvgl_tft/esp_lcd_backlight.h"
#include "lvgl_touch/touch_driver.h"

/* 屏幕方向设置 */
#define LV_PORTRAIT             0       /* 横屏 */
#define LV_PORTRAIT_INVERTED    0       /* 横屏倒置 */
#define LV_LANDSCAPE            1       /* 竖屏 */
#define LV_LANDSCAPE_INVERTED   0       /* 竖屏倒置 */

#if LV_PORTRAIT
#define LV_HOR_RES_MAX  320
#define LV_VER_RES_MAX  172
#define CONFIG_LV_DISPLAY_ORIENTATION   0
#endif

#if LV_PORTRAIT_INVERTED
#define LV_HOR_RES_MAX  320
#define LV_VER_RES_MAX  172
#define CONFIG_LV_DISPLAY_ORIENTATION   1
#endif

#if LV_LANDSCAPE
#define LV_HOR_RES_MAX  172
#define LV_VER_RES_MAX  320
#define CONFIG_LV_DISPLAY_ORIENTATION   2
#endif

#if LV_LANDSCAPE_INVERTED
#define LV_HOR_RES_MAX  172
#define LV_VER_RES_MAX  320
#define CONFIG_LV_DISPLAY_ORIENTATION   3
#endif

/*********************
 *      DEFINES
 *********************/

/* DISP_BUF_SIZE value doesn't have an special meaning, but it's the size
 * of the buffer(s) passed to LVGL as display buffers. The default values used
 * were the values working for the contributor of the display controller.
 *
 * As LVGL supports partial display updates the DISP_BUF_SIZE doesn't
 * necessarily need to be equal to the display size.
 *
 * When using RGB displays the display buffer size will also depends on the
 * color format being used, for RGB565 each pixel needs 2 bytes.
 * When using the mono theme, the display pixels can be represented in one bit,
 * so the buffer size can be divided by 8, e.g. see SSD1306 display size. */
#if defined (CONFIG_CUSTOM_DISPLAY_BUFFER_SIZE)
#define DISP_BUF_SIZE   CONFIG_CUSTOM_DISPLAY_BUFFER_BYTES
#else
#if defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7789)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * LV_VER_RES_MAX)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7735S
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ST7796S
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_HX8357
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SH1107
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * LV_VER_RES_MAX)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9481
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9486
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9488
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9341
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_SSD1306
#if defined (CONFIG_LV_THEME_MONO)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * (LV_VER_RES_MAX / 8))
#else
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * LV_VER_RES_MAX)
#endif
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_FT81X)
#define DISP_BUF_LINES  40
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * DISP_BUF_LINES)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_IL3820)
#define DISP_BUF_SIZE (LV_VER_RES_MAX * IL3820_COLUMNS)
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_RA8875
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_GC9A01)
#define DISP_BUF_SIZE  (LV_HOR_RES_MAX * 40)
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_JD79653A)
#define DISP_BUF_SIZE ((LV_VER_RES_MAX * LV_VER_RES_MAX) / 8) // 5KB
#elif defined (CONFIG_LV_TFT_DISPLAY_CONTROLLER_UC8151D)
#define DISP_BUF_SIZE ((LV_VER_RES_MAX * LV_VER_RES_MAX) / 8) // 2888 bytes
#elif defined CONFIG_LV_TFT_DISPLAY_CONTROLLER_ILI9163C
#define DISP_BUF_SIZE (LV_HOR_RES_MAX * 40)
#else
#error "No display controller selected"
#endif
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void lvgl_i2c_locking(void* leader);

/* Initialize detected SPI and I2C bus and devices */
void lvgl_driver_init(void);

/* Initialize SPI master  */
bool lvgl_spi_driver_init(int host, int miso_pin, int mosi_pin, int sclk_pin,
    int max_transfer_sz, int dma_channel, int quadwp_pin, int quadhd_pin);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LVGL_HELPERS_H */
