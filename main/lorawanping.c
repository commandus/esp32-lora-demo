#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state-display.h"
#include "lmic-ping.h"
#include "wifi-scan.h"

PingState pingState;

void app_main(void)
{
	pingStateInit(&displayEvent);

	displayInit();

	wifiScanInit();

	lmicPingInit();
	// xTaskCreate(lmicPingTask, "Lora", 4096, &pingState, 1, NULL);	// 5000

	lmicPingTask(NULL);
}
