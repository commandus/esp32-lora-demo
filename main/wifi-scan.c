#include "wifi-scan.h"

#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>

#define LOG_TAG_WIFI "WiFi" 

extern PingState pingState;

esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
		case SYSTEM_EVENT_STA_START:
			ESP_LOGI(LOG_TAG_WIFI, "Start");
			esp_wifi_connect();
			break;
		case SYSTEM_EVENT_STA_GOT_IP:
			ESP_LOGI(LOG_TAG_WIFI, "Connected with IP Address:");
			break;
		case SYSTEM_EVENT_STA_DISCONNECTED:
			esp_wifi_connect();
			break;
		default:
			break;
	}
    return ESP_OK;
}

void wifiScanInit()
{
	esp_netif_init();
	esp_event_loop_init(event_handler, NULL);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	cfg.nvs_enable = false;
	esp_wifi_init(&cfg);
	esp_wifi_set_mode(WIFI_MODE_AP);
	wifi_config_t wifi_config = {
		.ap = {
			.ssid = "ESP32-Access-Point",
			.password = "123456789",
			.ssid_len = 0,
        	.channel = 1,
        	.authmode = WIFI_AUTH_WPA2_PSK,
        	.ssid_hidden = false,
        	.max_connection = 4,
        	.beacon_interval = 100
		}
	};

	esp_wifi_set_config(WIFI_IF_AP, &wifi_config);

    esp_wifi_start();
}
