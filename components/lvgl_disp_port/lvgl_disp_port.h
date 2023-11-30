#ifndef __LVGL_PORT_H
#define __LVGL_POTT_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_freertos_hooks.h"

#include "lvgl.h"
#include "lvgl_helpers.h"

void lv_port_disp_init(void);
void disp_task_create(void);



#endif