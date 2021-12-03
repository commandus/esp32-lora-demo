#ifndef LMIC_PING_H_
#define LMIC_PING_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "ping-state.h"

void lmicPingInit(PingState *value);

void lmicPingTask(void *env);

#endif
