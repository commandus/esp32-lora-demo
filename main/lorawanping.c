#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blink.h"
#include "state-display.h"
#include "lmic-ping.h"

void app_main(void)
{
	PingState pingState;
	pingStateInit(&pingState);

	blinkInit(&pingState);
	xTaskCreate(blinkTask, "Blink", 512, &pingState, 1, NULL);

	displayInit(&pingState);
	xTaskCreate(displayTask, "Display", 1024, &pingState, 1, NULL);

	lmicPingInit(&pingState);
	xTaskCreate(lmicPingTask, "Lora", 8000, &pingState, 1, NULL);	// 5000

	while (1) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	// esp_restart();
}
