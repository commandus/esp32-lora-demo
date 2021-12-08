#include "ping-state.h"

extern PingState pingState;

void pingStateInit(ev_t_cb cb)
{
	pingState.txQueuedCount = 0;
	pingState.txCompleteCount = 0;
	pingState.lmicModemState = LMS_NONE;
	pingState.lmicEvent = EV_SCAN_TIMEOUT;
	pingState.evCallback = cb;
}
