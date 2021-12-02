#include "ping-state.h"

void blinkInit(PingState *pingState);

/*
	Blink LED task
	Usage:
		struct PingState pingState;
		blinkInit(&pingState);
	 	xTaskCreate(blinkTask, "Blink", 100, &pingState, 1, NULL);
*/

void blinkTask(void *env);
