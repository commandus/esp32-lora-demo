#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <nvs_flash.h>

#include "state-display.h"
#include "lmic-cli.h"
// #include "wifi-scan.h"
#include "ble-gatt-server.h"

// @see https://github.com/mcci-catena/ibm-lmic

#include "debug.h"

ProbeState probeState;

/*
static int cnt = 0;
static void initfunc01 (osjob_t* job) {
    // say hello
    debug_str("Hello World!\r\n");
    // log counter
    debug_val("cnt = ", cnt);
    // toggle LED
    debug_led(++cnt & 1);
    // reschedule job every second
    os_setTimedCallback(job, os_getTime()+sec2osticks(1), initfunc01);
}

// initial job
static void initfunc02 (osjob_t* j) {
    // reset MAC state
    LMIC_reset();
    // start joining
    LMIC_startJoining();
    // init done - onEvent() callback will be invoked...
}

void test01() {
	osjob_t initjob;
    // initialize runtime env
    os_init();
    // initialize debug library
    debug_init();
    // setup initial job
    os_setCallback(&initjob, initfunc01);
    // execute scheduled jobs and events
	lmicProbeTask();
}

void test02() {
	osjob_t initjob;

    // initialize runtime env
    os_init();
    // initialize debug library
    debug_init();
    // setup initial job
    os_setCallback(&initjob, initfunc02);
    // execute scheduled jobs and events
    lmicProbeTask();
    // (not reached)
}
*/

static char helloStr[5] = "hello";

void hello(char *buf, size_t sz) {
    text_message_ev_t value;
	value.tag = 'T';
    if (sz < sizeof(value.msg)) {
        memset(((char *) buf) + sz, 0, sizeof(value.msg) - sz);
        memmove(&value.msg, buf, sz);
    } else {
        memmove(&value.msg, buf, sizeof(value.msg));
    }
    sendTextMessage(&value);
}

void app_main()
{
	probeStateInit(&displayLoraEvent, &sendProbe);
	displayInit();

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

	// wifiScanInit();

	// test02();
	lmicProbeInit(false);

    while (1) {
        hello(helloStr, 5);
        os_runloop_once();
		vTaskDelay(10 * 1000 / portTICK_PERIOD_MS);
    }

    /*
	bleGattServerInit();
	lmicProbeTask();
    */
}
