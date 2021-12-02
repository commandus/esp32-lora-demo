#include "blink.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

void blinkInit(PingState *pingState)
{
    pingState->blinkCount = 0;
    /* 
       Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_reset_pin(BLINK_GPIO);
    // Set the GPIO as a push/pull output
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
}

void blinkTask(void *env) {
    PingState *pingState = (PingState *) env;
    while (1) {
        gpio_set_level(BLINK_GPIO, pingState->blinkCount % 2 ? 0 : 1);
        pingState->blinkCount++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
