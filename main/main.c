#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"
#include "lvgl_disp_port.h"
#include "lvgl_indev_port.h"
#include "lv_fs_if.h"
#include "app.h"
#include "fastscan.h"

void app_main(void)
{
    wifi_init();

    /* 1.LVGL内核、显示、输入和文件系统初始化 */
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_fs_if_init();
    
    /* 2.app demo */
    gui_demo();

    /* 3.任务创建 */
    input_task_create();
    disp_task_create();
}


