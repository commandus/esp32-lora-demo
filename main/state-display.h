#include "ping-state.h"

void displayInit(PingState *pingState);

/*
	Display state task
	Usage:
		struct PingState pingState;
		displayInit(&pingState);
	 	xTaskCreate(displayTask, "Display", 1000, &pingState, 1, NULL);
*/

void displayTask(void *env);
