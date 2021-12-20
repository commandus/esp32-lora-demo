#ifndef LMIC_ABP_H_
#define LMIC_ABP_H_	1

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "probe-state.h"

void lmicABPProbeInit();

#endif
