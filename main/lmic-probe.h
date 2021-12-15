#ifndef LMIC_PING_H_
#define LMIC_PING_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "probe-state.h"

void lmicProbeInit();

void lmicProbeTask(void *env);

void sendProbe(probe_ev_t *probe);

void sendTextMessage(text_message_ev_t *value);

#endif
