#include "lmic-probe.h"

#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"

/*
https://github.com/matthijskooijman/arduino-lmic/blob/master/examples/ttn-abp/ttn-abp.ino
*/

static uint8_t NWKSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
// LoRaWAN AppSKey, application session key
static uint8_t APPSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };
// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0x01450340 ; // 01450330 <-- Change this address for every node!

#define TX_INTERVAL 60
static osjob_t sendjob;

// Pin mapping 
const lmic_pinmap lmic_pins = {
    .nss = 5,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {26, 34, LMIC_UNUSED_PIN},	// 0- 26, 1- 34, 2- 35
    .spi = {19, 23, 18}		// MISO, MOSI, SCK
};

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).
void os_getArtEui (u1_t* buf) { }
void os_getDevEui (u1_t* buf) { }
void os_getDevKey (u1_t* buf) { }

extern ProbeState probeState;

probe_ev_t probeEventCopy;

#define LOG_TAG_LMIC "lora-probe" 

void sendProbeJob(osjob_t* job)
{
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        ESP_LOGI(LOG_TAG_LMIC, "OP_TXRXPEND, not sending");
        // Schedule next transmission
        // os_setTimedCallback(job, os_getTime() + sec2osticks(TX_INTERVAL), sendProbeJob);
    } else {
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, (void*) &probeEventCopy, sizeof(probe_ev_t), 0);
		probeState.txQueuedCount++;
        ESP_LOGI(LOG_TAG_LMIC, "Packet queued");
        probeState.loraEventCallback(0);
    }
}

void lmicProbeInit()
{
	// LMIC init
    os_init();
	// Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();
    LMIC_setSession(1, DEVADDR, NWKSKEY, APPSKEY);

    LMIC_setupChannel(0, 868900000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);
    LMIC_setupChannel(1, 869100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);

	// Disable link check validation
    LMIC_setLinkCheckMode(0);

    // TTN uses SF9 for its RX2 window.
    LMIC.dn2Dr = DR_SF9;
    LMIC.freq = 869100000;
  	// Use a medium spread factor. This can be increased up to SF12 for
  	// better range, but then the interval should be (significantly)
  	// lowered to comply with duty cycle limits as well.
    LMIC.datarate = DR_SF9;

    // Set data rate and transmit power for uplink (note: txpow seems to be ignored by the library)
    LMIC.txpow = 14;
    LMIC_setDrTxpow(DR_SF7, 14);

  	// This sets CR 4/5, BW125 (except for DR_SF7B, which uses BW250)
  	// LMIC.rps = updr2rps(LMIC.datarate);

    probeState.lmicModemState = LMS_INIT_SUCCESS;
}

void onEvent(ev_t ev) {
	probeState.loraEventCallback(ev);
	
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            ESP_LOGI(LOG_TAG_LMIC, "EV_SCAN_TIMEOUT");
            break;
        case EV_BEACON_FOUND:
            ESP_LOGI(LOG_TAG_LMIC, "EV_BEACON_FOUND");
            break;
        case EV_BEACON_MISSED:
            ESP_LOGI(LOG_TAG_LMIC, "EV_BEACON_MISSED");
            break;
        case EV_BEACON_TRACKED:
            ESP_LOGI(LOG_TAG_LMIC, "EV_BEACON_TRACKED");
            break;
        case EV_JOINING:
            ESP_LOGI(LOG_TAG_LMIC, "EV_JOINING");
            break;
        case EV_JOINED:
            ESP_LOGI(LOG_TAG_LMIC, "EV_JOINED");
            break;
        case EV_RFU1:
            ESP_LOGI(LOG_TAG_LMIC, "EV_RFU1");
            break;
        case EV_JOIN_FAILED:
            ESP_LOGI(LOG_TAG_LMIC, "EV_JOIN_FAILED");
            break;
        case EV_REJOIN_FAILED:
            ESP_LOGI(LOG_TAG_LMIC, "EV_REJOIN_FAILED");
            break;
        case EV_TXCOMPLETE:
            ESP_LOGI(LOG_TAG_LMIC, "EV_TXCOMPLETE (includes waiting for RX windows)");
			probeState.txCompleteCount++;

            if (LMIC.txrxFlags & TXRX_ACK)
              	ESP_LOGI(LOG_TAG_LMIC, "Received ack");
            if (LMIC.dataLen) {
				ESP_LOGI(LOG_TAG_LMIC, "Payload");
            }
			// Schedule next transmission
            // os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), sendProbeJob);
            break;
        case EV_LOST_TSYNC:
            ESP_LOGI(LOG_TAG_LMIC, "EV_LOST_TSYNC");
            break;
        case EV_RESET:
            ESP_LOGI(LOG_TAG_LMIC, "EV_RESET");
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            ESP_LOGI(LOG_TAG_LMIC, "EV_RXCOMPLETE");
            break;
        case EV_LINK_DEAD:
            ESP_LOGI(LOG_TAG_LMIC, "EV_LINK_DEAD");
            break;
        case EV_LINK_ALIVE:
            ESP_LOGI(LOG_TAG_LMIC, "EV_LINK_ALIVE");
            break;
        case EV_REINIT_REQUEST:
            ESP_LOGI(LOG_TAG_LMIC, "EV_REINIT_REQUEST");
            lmicProbeInit();
            break;
        default:
            ESP_LOGI(LOG_TAG_LMIC, "Unknown event");
            break;
    }
}

void lmicProbeTask(void *env)
{
	
    while (1) {
        os_runloop_once();
		vTaskDelay(10 * 1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void sendProbe(probe_ev_t *probe)
{
    if (probe)
        memmove(&probeEventCopy, probe, sizeof(probe_ev_t));
    sendProbeJob(&sendjob);
}