#ifndef LMIC_CLI_H_
#define LMIC_CLI_H_	1

#include "probe-state.h"

void lmicSetOTAA(bool on);

void lmicProbeInit();

void lmicProbeTask(void *env);

void sendProbe(probe_ev_t *probe);

void sendTextMessage(text_message_ev_t *value);

#endif
