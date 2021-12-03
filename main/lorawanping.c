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
	xTaskCreate(blinkTask, "Blink", 1000, &pingState, 1, NULL);

	displayInit(&pingState);
	xTaskCreate(displayTask, "Display", 1000, &pingState, 1, NULL);

	lmicPingInit(&pingState);
	xTaskCreate(lmicPingTask, "Lora", 1000, &pingState, 1, NULL);

	while (1) {
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	// esp_restart();
}
