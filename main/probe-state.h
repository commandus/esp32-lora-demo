#ifndef PROBE_STATE_H_
#define PROBE_STATE_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "ssd/ssd1306.h"
#include "lmic.h"

typedef enum
{
	LMS_NONE = 0,
	LMS_INIT_SUCCESS = 1,
	LMS_INIT_FAILURE = 2,
} LMIC_MODEM_STATE;

typedef struct {
	uint8_t tag;	// 'B'- bluetooth 'W'- Wi-Fi
	int8_t rssi;
	uint8_t mac[6];

} probe_ev_t;

typedef void(*lora_ev_t_cb)(ev_t);

typedef void(*probe_ev_t_cb)(probe_ev_t*);

typedef struct 
{
	uint32_t txQueuedCount;
	uint32_t txCompleteCount;
	SSD1306_t ssdDev;
	LMIC_MODEM_STATE lmicModemState;
	ev_t lmicEvent;
	lora_ev_t_cb loraEventCallback;
	probe_ev_t_cb probeEventCallback;
} ProbeState;

void probeStateInit(lora_ev_t_cb loraCallback, probe_ev_t_cb probeCallback);

#endif
