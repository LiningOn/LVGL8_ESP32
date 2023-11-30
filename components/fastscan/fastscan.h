#ifndef __FASTSCAN_H
#define __FASTSCAN_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

#if 0
#define WIFI_SSID       "NR_2.4GHz"
#define WIFI_PASSWORD   "1234abcd%"
#endif

#if 0
#define WIFI_SSID       "Redmi"
#define WIFI_PASSWORD   "lin111983"
#endif

#if 1
#define WIFI_SSID       "TP-LINK_4392"
#define WIFI_PASSWORD   "lhc12345678"
#endif

extern uint16_t wifi_ip_addr[4];
extern bool wifi_ip_got_state;

void wifi_init(void);
void wifi_start(void);
void wifi_stop(void);

#endif