#ifndef PING_STATE_H_
#define PING_STATE_H_	1

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

typedef void(*ev_t_cb)(ev_t);

typedef struct 
{
	uint32_t txQueuedCount;
	uint32_t txCompleteCount;
	SSD1306_t ssdDev;
	LMIC_MODEM_STATE lmicModemState;
	ev_t lmicEvent;
	ev_t_cb evCallback;
} PingState;

void pingStateInit(ev_t_cb cb);

#endif
