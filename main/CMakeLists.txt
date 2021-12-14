idf_component_register(SRCS "lorawanprobe.c" 
   "ssd/ssd1306.c" "ssd/ssd1306_i2c.c" "ssd/ssd1306_spi.c"
   "probe-state.c" "state-display.c" "lmic-probe.c"
   "ble-gatt-server.c"
   INCLUDE_DIRS "." "ssd")
