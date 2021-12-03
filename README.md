# lorawanping

Rebooting...
ets Jun  8 2016 00:22:57

rst:0xc (SW_CPU_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:7000
load:0x40078000,len:14308
load:0x40080400,len:3716
0x40080400: _init at ??:?

entry 0x40080680
I (27) boot: ESP-IDF v4.3.1-dirty 2nd stage bootloader
I (27) boot: compile time 13:22:36
I (27) boot: chip revision: 1
I (30) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (37) boot.esp32: SPI Speed      : 40MHz
I (42) boot.esp32: SPI Mode       : DIO
I (47) boot.esp32: SPI Flash Size : 4MB
I (51) boot: Enabling RNG early entropy source...
I (57) boot: Partition Table:
I (60) boot: ## Label            Usage          Type ST Offset   Length
I (67) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (75) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (82) boot:  2 factory          factory app      00 00 00010000 00100000
I (90) boot: End of partition table
I (94) boot_comm: chip revision: 1, min. application chip revision: 0
I (101) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=0bb7ch ( 47996) map
I (127) esp_image: segment 1: paddr=0001bba4 vaddr=3ffb0000 size=02a24h ( 10788) load
I (132) esp_image: segment 2: paddr=0001e5d0 vaddr=40080000 size=01a48h (  6728) load
I (136) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=1cda0h (118176) map
I (184) esp_image: segment 4: paddr=0003cdc8 vaddr=40081a48 size=0bab4h ( 47796) load
I (204) esp_image: segment 5: paddr=00048884 vaddr=50000000 size=00010h (    16) load
I (211) boot: Loaded app from partition at offset 0x10000
I (211) boot: Disabling RNG early entropy source...
I (224) cpu_start: Pro cpu up.
I (224) cpu_start: Starting app cpu, entry point is 0x400811ac
0x400811ac: call_start_cpu1 at /home/andrei/esp/esp-idf/components/esp_system/port/cpu_start.c:141

I (211) cpu_start: App cpu up.
I (239) cpu_start: Pro cpu start user code
I (239) cpu_start: cpu freq: 160000000
I (239) cpu_start: Application information:
I (243) cpu_start: Project name:     lorawanping
I (248) cpu_start: App version:      5c58261-dirty
I (254) cpu_start: Compile time:     Dec  3 2021 13:22:26
I (260) cpu_start: ELF file SHA256:  fc630a98ed14434c...
I (266) cpu_start: ESP-IDF:          v4.3.1-dirty
I (272) heap_init: Initializing. RAM available for dynamic allocation:
I (279) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (285) heap_init: At 3FFB35E0 len 0002CA20 (178 KiB): DRAM
I (291) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (297) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (304) heap_init: At 4008D4FC len 00012B04 (74 KiB): IRAM
I (311) spi_flash: detected chip: generic
I (315) spi_flash: flash io: dio
I (320) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
I (330) gpio: GPIO[19]| InputEn: 0| OutputEn: 0| OpenDrain: 0| Pullup: 1| Pulldown: 0| Intr:0 
I (340) Display: INTERFACE is i2c
I (340) Display: CONFIG_SDA_GPIO=21
I (350) Display: CONFIG_SCL_GPIO=22
I (350) Display: CONFIG_RESET_GPIO=-1
I (360) Display: Panel is 128x64
I (360) SSD1306: OLED configured successfully
I (460) lmic: Starting IO initialization
I (460) gpio: GPIO[5]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (470) gpio: GPIO[14]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (480) gpio: GPIO[26]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (490) gpio: GPIO[34]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (490) gpio: GPIO[35]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (500) lmic: Finished IO initialization
I (510) lmic: Starting SPI initialization
I (510) lmic: Finished SPI initialization
I (520) lmic: Starting initialisation of timer
I (520) lmic: Finished initalisation of timer
I (530) gpio: GPIO[14]| InputEn: 0| OutputEn: 1| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (540) lmic: Wait until
I (540) lmic: Done waiting until
I (540) gpio: GPIO[14]| InputEn: 1| OutputEn: 0| OpenDrain: 0| Pullup: 0| Pulldown: 0| Intr:0 
I (550) lmic: Wait until
I (650) lmic: Done waiting until
I (860) lora-ping: Packet queued
I (1930) lmic: Wait until
I (1930) lmic: Done waiting until
E (1930) spi_master: check_trans_valid(694): txdata transfer > host maximum
assertion "ret == ESP_OK" failed: file "../components/lmic-esp-idf/src/hal/hal.c", line 149, function: hal_spi

abort() was called at PC 0x400deceb on core 0
0x400deceb: __assert_func at /builds/idf/crosstool-NG/.build/xtensa-esp32-elf/src/newlib/newlib/libc/stdlib/assert.c:62 (discriminator 8)


Backtrace:0x400866a3:0x3ffb85e0 0x40086df5:0x3ffb8600 0x4008c43e:0x3ffb8620 0x400deceb:0x3ffb8690 0x400d9ef9:0x3ffb86c0 0x400d8eac:0x3ffb8720 0x400d8ec5:0x3ffb8740 0x400d8f7e:0x3ffb8760 0x400d90c6:0x3ffb8780 0x400d9527:0x3ffb87a0 0x400d70b7:0x3ffb87c0 0x400d70c2:0x3ffb87e0 0x400d8d17:0x3ffb8800 0x400d64ec:0x3ffb8820 0x40089751:0x3ffb8840
0x400866a3: panic_abort at /home/andrei/esp/esp-idf/components/esp_system/panic.c:368

0x40086df5: esp_system_abort at /home/andrei/esp/esp-idf/components/esp_system/system_api.c:112

0x4008c43e: abort at /home/andrei/esp/esp-idf/components/newlib/abort.c:46

0x400deceb: __assert_func at /builds/idf/crosstool-NG/.build/xtensa-esp32-elf/src/newlib/newlib/libc/stdlib/assert.c:62 (discriminator 8)

0x400d9ef9: hal_spi at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:149 (discriminator 1)

0x400d8eac: readReg at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/radio.c:272

0x400d8ec5: opmode at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/radio.c:297

0x400d8f7e: rxlora at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/radio.c:584

0x400d90c6: startrx at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/radio.c:664

0x400d9527: os_radio at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/radio.c:842

0x400d70b7: setupRx1 at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/lmic.c:1392

0x400d70c2: setupRx1DnData at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/lmic.c:1604

