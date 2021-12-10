#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "state-display.h"
#include "lmic-probe.h"
#include "wifi-scan.h"

ProbeState probeState;

void app_main(void)
{
	probeStateInit(&displayLoraEvent, &sendProbe);

	displayInit();

	wifiScanInit();

	lmicProbeInit();
	// xTaskCreate(lmicPingTask, "Lora", 4096, &pingState, 1, NULL);	// 5000

	lmicProbeTask(NULL);
}
