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

#define LOG_TAG "SSD1306" 

void displayInit(PingState *pingState)
{
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(LOG_TAG, "INTERFACE is i2c");
	ESP_LOGI(LOG_TAG, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
	i2c_master_init(&pingState->ssdDev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(LOG_TAG, "INTERFACE is SPI");
	ESP_LOGI(LOG_TAG, "CONFIG_MOSI_GPIO=%d", CONFIG_MOSI_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_SCLK_GPIO=%d", CONFIG_SCLK_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_CS_GPIO=%d", CONFIG_CS_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_DC_GPIO=%d", CONFIG_DC_GPIO);
	ESP_LOGI(LOG_TAG, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
	spi_master_init(&pingState->ssdDev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	pingState->ssdDev._flip = true;
	ESP_LOGW(LOG_TAG, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(LOG_TAG, "Panel is 128x64");
	ssd1306_init(&pingState->ssdDev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(LOG_TAG, "Panel is 128x32");
	ssd1306_init(&pingState->ssdDev, 128, 32);
	lines = 4;
#endif // CONFIG_SSD1306_128x32

	ssd1306_clear_screen(&pingState->ssdDev, false);
	ssd1306_contrast(&pingState->ssdDev, 0xff);

	ssd1306_display_text(&pingState->ssdDev, 0, "lorawan-ping", 12, false);

#if CONFIG_SSD1306_128x64
	ssd1306_display_text(&pingState->ssdDev, 7, "128x64", 6, false);
#endif // CONFIG_SSD1306_128x64

#if CONFIG_SSD1306_128x32
	ssd1306_display_text(&pingState->ssdDev, 7, "128x32", 6, false);
#endif // CONFIG_SSD1306_128x32
}

void updateScreen(PingState *pingState) 
{
	// ssd1306_clear_line(&pingState->ssdDev, 2, false);
	char line[12];
	int sz = snprintf(line, sizeof(line), "T: %6d", pingState->blinkCount);
	ssd1306_display_text(&pingState->ssdDev, 2, line, sz, false);
}

void displayTask(void *env) 
{
    PingState *pingState = (PingState *) env;
    while (1) {
		updateScreen(pingState);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
