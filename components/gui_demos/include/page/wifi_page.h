#ifndef WIFI_PAGE_H
#define WIFI_PAGE_H

#include "esp_log.h"
#include "lvgl.h"
#include "bg_cont_page.h"
#include "anim.h"
#include "main_menu_page.h"
#include "fastscan.h"
#include "config.h"

typedef enum wifi_state{
    WIFI_STATE_OPENED,
    WIFI_STATE_CLOSED,
}wifi_state_t;

void wifi_page(uint32_t delay);

#endif