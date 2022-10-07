#ifndef LMIC_CLI_H_
#define LMIC_CLI_H_	1

#include "probe-state.h"

void lmicProbeInit(bool otaa);

void lmicProbeTask();

void sendProbe(probe_ev_t *probe);

void sendTextMessage(text_message_ev_t *value);

#endif
