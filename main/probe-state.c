#include "probe-state.h"

extern ProbeState probeState;

void probeStateInit(lora_ev_t_cb loraCallback, probe_ev_t_cb probeCallback)
{
	probeState.txQueuedCount = 0;
	probeState.txCompleteCount = 0;
	probeState.txPendingCount = 0;
	probeState.lmicModemState = LMS_NONE;
	probeState.lmicEvent = EV_SCAN_TIMEOUT;
	probeState.loraEventCallback = loraCallback;
	probeState.probeEventCallback = probeCallback;
}
