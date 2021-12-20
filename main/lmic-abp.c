#include "lmic-abp.h"

#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"

/*
https://github.com/matthijskooijman/arduino-lmic/blob/master/examples/ttn-abp/ttn-abp.ino
*/

extern uint8_t NWKSKEY[16];
// LoRaWAN AppSKey, application session key
extern uint8_t APPSKEY[16];

// LoRaWAN end-device address (DevAddr)
static const u4_t DEVADDR = 0x01450340 ; // 01450330 <-- Change this address for every node!

#define TX_INTERVAL 60

static osjob_t sendjob;

extern ProbeState probeState;

#define LOG_TAG_ABP "lora-abp" 

void lmicABPProbeInit()
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
