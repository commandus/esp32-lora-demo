#ifndef LMIC_OTAA_H_
#define LMIC_OTAA_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "probe-state.h"

void lmicOTAAProbeInit();

#endif
