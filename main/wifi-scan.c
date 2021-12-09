#include "wifi-scan.h"

#include <esp_system.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <nvs_flash.h>


#define LOG_TAG_WIFI "WiFi" 

extern PingState pingState;

// Initialize NVS

static void nvsInit() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    	ESP_ERROR_CHECK(nvs_flash_erase());
      	ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
	switch(event_id) {
		case WIFI_EVENT_AP_START:
		{
        	ESP_LOGI(LOG_TAG_WIFI, "Started");
		}
		break;
    	case WIFI_EVENT_AP_STACONNECTED:
		{
        	wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        	ESP_LOGI(LOG_TAG_WIFI, "station "MACSTR" join, AID=%d", MAC2STR(event->mac), event->aid);
		}
		break;
    	case WIFI_EVENT_AP_STADISCONNECTED:
		{
			wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
			ESP_LOGI(LOG_TAG_WIFI, "station "MACSTR" leave, AID=%d", MAC2STR(event->mac), event->aid);
		}
		break;
		case WIFI_EVENT_AP_PROBEREQRECVED:
		{
			wifi_event_ap_probe_req_rx_t *event = (wifi_event_ap_probe_req_rx_t*) event_data;
			ESP_LOGI(LOG_TAG_WIFI, "Probe "MACSTR" rssi: %d", MAC2STR(event->mac), event->rssi);
		}
		break;
		default:
			ESP_LOGI(LOG_TAG_WIFI, "Event %d", event_id);
    }
}

void wifiScanInit()
{
	nvsInit();

	ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	// cfg.nvs_enable = false;
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
		ESP_EVENT_ANY_ID,
		&wifi_event_handler,
		NULL,
		NULL));

	wifi_config_t wifi_config = {
		.ap = {
			.ssid = "LORAWAN-WIFI-TRAP",
			.password = "123456789",
			.ssid_len = 0,
        	.channel = 1,
        	.authmode = WIFI_AUTH_WPA2_PSK,
        	.ssid_hidden = false,
        	.max_connection = 4,
        	.beacon_interval = 100
		}
	};

	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_event_mask(WIFI_EVENT_MASK_NONE));
	ESP_ERROR_CHECK(esp_wifi_start());
	
    ESP_LOGI(LOG_TAG_WIFI, "wifi_init_softap finished. SSID:%s password: %s channel: %d",
        wifi_config.ap.ssid, wifi_config.ap.password, wifi_config.ap.channel);
}
