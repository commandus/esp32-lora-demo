#include "state-display.h"

#include "esp_log.h"
#include "ssd/ssd1306.h"
// #include "ssd/font8x8_basic.h"


/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO
    CONFIG_FLIP
	CONFIG_SSD1306_128x64
	CONFIG_SSD1306_128x32
	CONFIG_I2C_INTERFACE | CONFIG_SPI_INTERFACE
		- CONFIG_I2C_INTERFACE
			CONFIG_MOSI_GPIO
			CONFIG_SCLK_GPIO
			CONFIG_SDA_GPIO
			CONFIG_RESET_GPIO
		- CONFIG_SPI_INTERFACE
			CONFIG_CS_GPIO
			CONFIG_DC_GPIO
			CONFIG_RESET_GPIO
*/

#define LOG_TAG_DISPLAY "Display" 

extern PingState pingState;

void displayInit()
{
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(LOG_TAG_DISPLAY, "INTERFACE is i2c");
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
	i2c_master_init(&pingState.ssdDev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(LOG_TAG_DISPLAY, "INTERFACE is SPI");
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_MOSI_GPIO=%d", CONFIG_MOSI_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_SCLK_GPIO=%d", CONFIG_SCLK_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_CS_GPIO=%d", CONFIG_CS_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_DC_GPIO=%d", CONFIG_DC_GPIO);
	ESP_LOGI(LOG_TAG_DISPLAY, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
	spi_master_init(&pingState.ssdDev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	pingState.ssdDev._flip = true;
	ESP_LOGW(LOG_TAG_DISPLAY, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(LOG_TAG_DISPLAY, "Panel is 128x64");
	ssd1306_init(&pingState.ssdDev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(LOG_TAG_DISPLAY, "Panel is 128x32");
	ssd1306_init(&pingState.ssdDev, 128, 32);
	lines = 4;
#endif // CONFIG_SSD1306_128x32

	ssd1306_clear_screen(&pingState.ssdDev, false);
	ssd1306_contrast(&pingState.ssdDev, 0xff);

	ssd1306_display_text(&pingState.ssdDev, 0, "lorawan-ping", 12, false);

#if CONFIG_SSD1306_128x64
#endif // CONFIG_SSD1306_128x64

#if CONFIG_SSD1306_128x32
#endif // CONFIG_SSD1306_128x32
}

static LMIC_MODEM_STATE oldState = LMS_NONE;

void updateScreen() 
{
	
	char line[17];	// 128 / 8 = 16 + trailing /0

	if (oldState != pingState.lmicModemState) {
		// state
		oldState = pingState.lmicModemState;
		switch (pingState.lmicModemState) {
			case LMS_INIT_SUCCESS:
				ssd1306_display_text(&pingState.ssdDev, 3, "Running", 7, false);
				break;
			case LMS_INIT_FAILURE:
				ssd1306_display_text(&pingState.ssdDev, 3, "Failure", 7, false);
				break;
			default:
				ssd1306_display_text(&pingState.ssdDev, 3, "LMIC", 4, false);
				break;
		}
	}

	ssd1306_clear_line(&pingState.ssdDev, 4, false);
	switch(pingState.lmicEvent) {
		case EV_SCAN_TIMEOUT:
			ssd1306_display_text(&pingState.ssdDev, 4, "Scan timeout", 12, false);
			break;
		case EV_BEACON_FOUND:
			ssd1306_display_text(&pingState.ssdDev, 4, "Beacon found", 12, false);
			break;
		case EV_BEACON_MISSED:
			ssd1306_display_text(&pingState.ssdDev, 4, "Beacon miss", 11, false);
			break;
		case EV_BEACON_TRACKED:
			ssd1306_display_text(&pingState.ssdDev, 4, "Beacon track", 12, false);
			break;
		case EV_JOINING:
			ssd1306_display_text(&pingState.ssdDev, 4, "Joining", 7, false);
			break;
		case EV_JOINED:
			ssd1306_display_text(&pingState.ssdDev, 4, "Joined", 6, false);
			break;
		case EV_RFU1:
			ssd1306_display_text(&pingState.ssdDev, 4, "RFU1", 4, false);
			break;
		case EV_JOIN_FAILED:
			ssd1306_display_text(&pingState.ssdDev, 4, "Join failed", 11, false);
			break;
		case EV_REJOIN_FAILED:
			ssd1306_display_text(&pingState.ssdDev, 4, "Rejoin failed", 13, false);
			break;
		case EV_LOST_TSYNC:
			ssd1306_display_text(&pingState.ssdDev, 4, "Lost TSYNC", 10, false);
			break;
		case EV_RESET:
			ssd1306_display_text(&pingState.ssdDev, 4, "Reset", 5, false);
			break;
		case EV_RXCOMPLETE:
			// data received in ping slot
			ssd1306_display_text(&pingState.ssdDev, 4, "RX complete", 11, false);
			break;
		case EV_LINK_DEAD:
			ssd1306_display_text(&pingState.ssdDev, 4, "Link read", 9, false);
			break;
		case EV_LINK_ALIVE:
			ssd1306_display_text(&pingState.ssdDev, 4, "Link alive", 10, false);
			break;
		default:	//EV_TXCOMPLETE:
			{
				size_t sz = snprintf(line, sizeof(line), "TX %d:%d", pingState.txQueuedCount, pingState.txCompleteCount);
				ssd1306_display_text(&pingState.ssdDev, 4, line, sz, false);
				if (LMIC.txrxFlags & TXRX_ACK)
					ssd1306_display_text(&pingState.ssdDev, 4, "ACK", 3, false);
				if (LMIC.dataLen) {
						int sz = snprintf(line, sizeof(line), "Payload %6d", LMIC.dataLen);
						ssd1306_display_text(&pingState.ssdDev, 4, line, sz, false);
				}
			}
			break;
	}
}

void displayEvent(ev_t event)
{
	pingState.lmicEvent = event;
	updateScreen();
}
