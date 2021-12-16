#ifndef _lmic_config_h_
#define _lmic_config_h_

#include "sdkconfig.h"

// In the original LMIC code, these config values were defined on the
// gcc commandline. Since Arduino does not allow easily modifying the
// compiler commandline, use this file instead.

#ifdef CONFIG_LMIC_FREQ_USE_EU_868
#define CFG_eu868 1
#endif

#ifdef CONFIG_LMIC_FREQ_USE_US_915
#define CFG_us915 1
#endif
// This is the SX1272/SX1273 radio, which is also used on the HopeRF
// RFM92 boards.
#ifdef CONFIG_LMIC_USE_SX1272
#define CFG_sx1272_radio 1
#endif
// This is the SX1276/SX1277/SX1278/SX1279 radio, which is also used on
// the HopeRF RFM95 boards.
#ifdef CONFIG_LMIC_USE_SX1276
#define CFG_sx1276_radio 1
#endif

/*
 * In ESP32 RTC runs at 150.000 hz.
 *
 * Each RTC tick has a period of (100/15) usecs. If we factorize this value we have that
 * (100 / 15) usecs = ((2 * 5 * 2 * 4) / (3 * 5)) usecs = (20 / 3) usecs.
 *
 * LMIC needs a tick period between 15.5 usecs and 100 usecs, so we have to multiply RTC ticks
 * periods for give LMIC ticks periods. This causes, for example, that if we multiply RTC ticks
 * periods by 3 we have an exact period time of 20 usecs (20 / 3) usecs * 3 = 20 usecs.
 *
 * For that reason Lua RTOS is configured to count 1 LMIC tick every 3 RTC ticks, so, for LMIC:
 *
 * US_PER_OSTICK = 20
 * OSTICKS_PER_SEC = 50000
 *
 */
// 20 μs per tick
// LMIC requires ticks to be 15.5μs - 100 μs long
#define OSTICKS_PER_SEC 50000

// SPI interface used by LMIC
#ifdef CONFIG_LMIC_SPI_HSPI
#define LMIC_SPI HSPI_HOST
#endif

#ifdef CONFIG_LMIC_SPI_VSPI
#define LMIC_SPI VSPI_HOST
#endif

// Set this to 1 to enable some basic debug output (using printf) about
// RF settings used during transmission and reception. Set to 2 to
// enable more verbose output. Make sure that printf is actually
// configured (e.g. on AVR it is not by default), otherwise using it can
// cause crashing.
#define LMIC_DEBUG_LEVEL CONFIG_LMIC_DEBUG_LEVEL

// Uncomment this to disable all code related to joining
#ifndef CONFIG_LMIC_FEATURE_JOIN
#define DISABLE_JOIN
#endif
// Uncomment this to disable all code related to ping
#ifndef CONFIG_LMIC_FEATURE_PING
#define DISABLE_PING
#endif
// Uncomment this to disable all code related to beacon tracking.
// Requires ping to be disabled too
#ifndef CONFIG_LMIC_FEATURE_BEACONS
#define DISABLE_BEACONS
#endif

// Uncomment these to disable the corresponding MAC commands.
// Class A
//#define DISABLE_MCMD_DCAP_REQ // duty cycle cap
//#define DISABLE_MCMD_DN2P_SET // 2nd DN window param
//#define DISABLE_MCMD_SNCH_REQ // set new channel
// Class B
//#define DISABLE_MCMD_PING_SET // set ping freq, automatically disabled by DISABLE_PING
//#define DISABLE_MCMD_BCNI_ANS // next beacon start, automatical disabled by DISABLE_BEACON

// In LoRaWAN, a gateway applies I/Q inversion on TX, and nodes do the
// same on RX. This ensures that gateways can talk to nodes and vice
// versa, but gateways will not hear other gateways and nodes will not
// hear other nodes. By uncommenting this macro, this inversion is
// disabled and this node can hear other nodes. If two nodes both have
// this macro set, they can talk to each other (but they can no longer
// hear gateways). This should probably only be used when debugging
// and/or when talking to the radio directly (e.g. like in the "raw"
// example).
//#define DISABLE_INVERT_IQ_ON_RX

// This allows choosing between multiple included AES implementations.
// Make sure exactly one of these is uncommented.
//
// This selects the original AES implementation included LMIC. This
// implementation is optimized for speed on 32-bit processors using
// fairly big lookup tables, but it takes up big amounts of flash on the
// AVR architecture.
#define USE_ORIGINAL_AES
//
// This selects the AES implementation written by Ideetroon for their
// own LoRaWAN library. It also uses lookup tables, but smaller
// byte-oriented ones, making it use a lot less flash space (but it is
// also about twice as slow as the original).
// #define USE_IDEETRON_AES

#endif // _lmic_config_h_
