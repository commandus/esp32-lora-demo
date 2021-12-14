#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nvs_flash.h>

#include "state-display.h"
#include "lmic-probe.h"
// #include "wifi-scan.h"
#include "ble-gatt-server.h"

ProbeState probeState;

void app_main()
{
	probeStateInit(&displayLoraEvent, &sendProbe);

	displayInit();

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

	// wifiScanInit();

	lmicProbeInit();
	// xTaskCreate(lmicPingTask, "Lora", 4096, &pingState, 1, NULL);	// 5000

	bleGattServerInit();

	lmicProbeTask(NULL);
}
