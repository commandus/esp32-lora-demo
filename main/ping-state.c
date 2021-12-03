#include "ping-state.h"

void pingStateInit(PingState *value)
{
	value->blinkCount = 0;
	value->lmicModemState = LMS_NONE;
	value->lmicEvent = EV_SCAN_TIMEOUT;
}
