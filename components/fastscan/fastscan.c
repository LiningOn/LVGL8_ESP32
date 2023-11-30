#include "fastscan.h"

static const char *TAG = "scan";
uint16_t wifi_ip_addr[4];
bool wifi_ip_got_state;

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
    {
        ESP_LOGI(TAG, "CONNECTED");
        wifi_ip_got_state = false;
    }
    else if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(TAG, "DISCONNECTED:");
        wifi_ip_got_state = false;
        esp_wifi_connect();
    }
    else if(event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        
        wifi_ip_addr[0] = esp_ip4_addr1_16(&event->ip_info.ip);
        wifi_ip_addr[1] = esp_ip4_addr2_16(&event->ip_info.ip);
        wifi_ip_addr[2] = esp_ip4_addr3_16(&event->ip_info.ip);
        wifi_ip_addr[3] = esp_ip4_addr4_16(&event->ip_info.ip);
        wifi_ip_got_state = true;
        ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP: %d.%d.%d.%d", wifi_ip_addr[0], wifi_ip_addr[1], wifi_ip_addr[2], wifi_ip_addr[3]);
    }
}

void wifi_init(void)
{
    esp_err_t ret = nvs_flash_init();
    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_ERROR_CHECK(esp_netif_init());                      
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();                    

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();    
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));                   

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, 
                                                        ESP_EVENT_ANY_ID, 
                                                        &wifi_event_handler, 
                                                        NULL, 
                                                        NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));
                                                        
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASSWORD,              
            .scan_method = WIFI_FAST_SCAN,                  
            .sort_method = WIFI_CONNECT_AP_BY_SECURITY,     
            .threshold.rssi = -127,                         
            .threshold.authmode = WIFI_AUTH_OPEN            
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start(); 
    esp_wifi_stop();                     
}

void wifi_start(void)
{
    esp_wifi_start();
    esp_wifi_connect(); 
}

void wifi_stop(void)
{
    esp_wifi_stop();
}


