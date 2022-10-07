
#include "lmic-cli.h"
#include "lmic-abp.h"
#include "lmic-otaa.h"

#include "esp_log.h"

extern ProbeState probeState;

static osjob_t sendjob;

static bool initOTAA;

// Pin mapping 
const lmic_pinmap lmic_pins = {
    .nss = 5,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = { 26, 34, LMIC_UNUSED_PIN },	// 0- 26, 1- 34, 2- 35
    .spi = { 19, 23, 18 }       		// MISO, MOSI, SCK
};

uint8_t NWKSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

// LoRaWAN AppSKey, application session key
// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.
// The key shown here is the semtech default key.
uint8_t APPSKEY[16] = { 0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C };

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
const uint8_t APPSEUI[8] = { 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11 };

// little-endian format
const uint8_t DEVEUI[8] = { 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01 };

// This key should be in big endian format (or, since it is not really a
// number but a block of memory, endianness does not really apply). In
// practice, a key taken from ttnctl can be copied as-is.
// The key shown here is the semtech default key.
void os_getDevKey (u1_t* buf) { memcpy(buf, APPSKEY, 16); }

// These callbacks are only used in over-the-air activation, so they are
// left empty here (we cannot leave them out completely unless
// DISABLE_JOIN is set in config.h, otherwise the linker will complain).

// This EUI must be in little-endian format, so least-significant-byte
// first. When copying an EUI from ttnctl output, this means to reverse
// the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
// 0x70.
void os_getArtEui (u1_t* buf) { memcpy(buf, APPSEUI, 8); }
void os_getDevEui (u1_t* buf) { memcpy(buf, DEVEUI, 8); }

probe_ev_t probeEventCopy;
text_message_ev_t textMessageCopy;

#define LOG_TAG_LMIC "lora-cli" 

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
            // Disable link check validation (automatically enabled
            // during join, but not supported by TTN at this time).
            LMIC_setLinkCheckMode(0);
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
            ESP_LOGI(LOG_TAG_LMIC, "EV_TXCOMPLETE");
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
            lmicProbeInit(initOTAA);
            break;
        default:
            ESP_LOGI(LOG_TAG_LMIC, "Unknown event");
            break;
    }
}

static void sendProbeJob(osjob_t* job)
{
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        ESP_LOGI(LOG_TAG_LMIC, "OP_TXRXPEND, not sending");
        probeState.txPendingCount++;
        if (probeState.txPendingCount > 3) {
            esp_restart();
        }
    } else {
        probeState.txPendingCount = 0;
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, (void*) &probeEventCopy, sizeof(probe_ev_t), 0);
		probeState.txQueuedCount++;
        ESP_LOGI(LOG_TAG_LMIC, "Packet queued");
        probeState.loraEventCallback(0);
    }
}

static void sendTextMessageJob(osjob_t* job)
{
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        ESP_LOGI(LOG_TAG_LMIC, "OP_TXRXPEND, not sending");
        probeState.txPendingCount++;
        if (probeState.txPendingCount > 3) {
            esp_restart();
        }
    } else {
        probeState.txPendingCount = 0;
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, (void*) &textMessageCopy, sizeof(text_message_ev_t), 0);
		probeState.txQueuedCount++;
        ESP_LOGI(LOG_TAG_LMIC, "Text message queued");
        probeState.loraEventCallback(0);
    }
}

void lmicProbeInit(bool otaa)
{
    initOTAA = otaa;
    if (otaa)
        lmicOTAAProbeInit();
    else
        lmicABPProbeInit();
}

void lmicProbeTask()
{
    while (1) {
        os_runloop_once();
		vTaskDelay(10 * 1000 / portTICK_PERIOD_MS);
    }
}

void sendTextMessage(text_message_ev_t *value)
{
    if (value)
        memmove(&textMessageCopy, value, sizeof(text_message_ev_t));
    sendTextMessageJob(&sendjob);
}

void sendProbe(probe_ev_t *value)
{
    if (value)
        memmove(&probeEventCopy, value, sizeof(probe_ev_t));
    sendProbeJob(&sendjob);
}
