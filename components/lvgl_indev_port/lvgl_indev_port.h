#ifndef LVGL_PORT_INDEV_H
#define LVGL_PORT_INDEV_H

#include "lvgl.h"
#include "encoder.h"

void lv_port_indev_init(void);
lv_indev_t* get_indev(void);
lv_group_t* get_group(void);

#endif