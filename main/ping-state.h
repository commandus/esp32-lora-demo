#ifndef PING_STATE_H_
#define PING_STATE_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "ssd/ssd1306.h"

typedef struct 
{
	int blinkCount;
	SSD1306_t ssdDev;

} PingState;

void pingStateInit(PingState *value);

#endif
