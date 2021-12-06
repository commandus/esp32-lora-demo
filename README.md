# lorawanping

I (3231009) lora-ping: Packet queued
I (3232079) lmic: Wait until
I (3232079) lmic: Done waiting until
I (3233089) lmic: Wait until
I (3233089) lmic: Done waiting until
I (3233109) lora-ping: event
I (3233109) lora-ping: EV_TXCOMPLETE (includes waiting for RX windows)
E (3238119) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (3238119) task_wdt:  - IDLE (CPU 0)
E (3238119) task_wdt: Tasks currently running:
E (3238119) task_wdt: CPU 0: Lora
E (3238119) task_wdt: CPU 1: IDLE
E (3238119) task_wdt: Print CPU 0 (current core) backtrace


Backtrace:0x400DE2B8:0x3FFB07F0 0x40082519:0x3FFB0810 0x4000BFED:0x3FFBA0C0 0x4008986B:0x3FFBA0D0 0x400DD9BD:0x3FFBA0F0 0x400D9F11:0x3FFBA120 0x400D9F1B:0x3FFBA150 0x400D9F7D:0x3FFBA170 0x400D8CF1:0x3FFBA190 0x400D64F0:0x3FFBA1B0 0x40089751:0x3FFBA1D0 
0x400de2b8: task_wdt_isr at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:189

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x4008986b: xPortInIsrContext at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:378

0x400dd9bd: vPortEnterCriticalSafe at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/include/freertos/portmacro.h:221 (discriminator 2)
 (inlined by) timer_get_counter_value at /home/andrei/esp/esp-idf/components/driver/timer.c:68 (discriminator 2)

0x400d9f11: hal_ticks at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:182

0x400d9f1b: delta_time at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:189

0x400d9f7d: hal_checkTimer at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:209

0x400d8cf1: os_runloop_once at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/oslmic.c:113 (discriminator 1)

0x400d64f0: lmicPingTask at /home/andrei/src/esp32-lora-demo/build/../main/lmic-ping.c:158 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3238119) task_wdt: Print CPU 1 backtrace


Backtrace:0x40084A11:0x3FFB0DF0 0x40082519:0x3FFB0E10 0x4000BFED:0x3FFB76D0 0x400899BE:0x3FFB76E0 0x400DE4FC:0x3FFB7700 0x400DE507:0x3FFB7730 0x400D57A9:0x3FFB7750 0x4008813A:0x3FFB7770 0x40089751:0x3FFB7790 
0x40084a11: esp_crosscore_isr at /home/andrei/esp/esp-idf/components/esp32/crosscore_int.c:77

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400de4fc: esp_task_wdt_reset at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:336

0x400de507: idle_hook_cb at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:88

0x400d57a9: esp_vApplicationIdleHook at /home/andrei/esp/esp-idf/components/esp_common/src/freertos_hooks.c:51 (discriminator 1)

0x4008813a: prvIdleTask at /home/andrei/esp/esp-idf/components/freertos/tasks.c:3839 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3243119) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (3243119) task_wdt:  - IDLE (CPU 0)
E (3243119) task_wdt: Tasks currently running:
E (3243119) task_wdt: CPU 0: Lora
E (3243119) task_wdt: CPU 1: IDLE
E (3243119) task_wdt: Print CPU 0 (current core) backtrace


Backtrace:0x400DE2B8:0x3FFB07F0 0x40082519:0x3FFB0810 0x4000BFED:0x3FFBA0C0 0x4008986B:0x3FFBA0D0 0x400DD9BD:0x3FFBA0F0 0x400D9F11:0x3FFBA120 0x400D9F1B:0x3FFBA150 0x400D9F7D:0x3FFBA170 0x400D8CF1:0x3FFBA190 0x400D64F0:0x3FFBA1B0 0x40089751:0x3FFBA1D0 
0x400de2b8: task_wdt_isr at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:189

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x4008986b: xPortInIsrContext at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:378

0x400dd9bd: vPortEnterCriticalSafe at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/include/freertos/portmacro.h:221 (discriminator 2)
 (inlined by) timer_get_counter_value at /home/andrei/esp/esp-idf/components/driver/timer.c:68 (discriminator 2)

0x400d9f11: hal_ticks at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:182

0x400d9f1b: delta_time at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:189

0x400d9f7d: hal_checkTimer at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:209

0x400d8cf1: os_runloop_once at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/oslmic.c:113 (discriminator 1)

0x400d64f0: lmicPingTask at /home/andrei/src/esp32-lora-demo/build/../main/lmic-ping.c:158 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3243119) task_wdt: Print CPU 1 backtrace


Backtrace:0x40084A11:0x3FFB0DF0 0x40082519:0x3FFB0E10 0x4000BFED:0x3FFB76D0 0x400899BE:0x3FFB76E0 0x400DE4FC:0x3FFB7700 0x400DE507:0x3FFB7730 0x400D57A9:0x3FFB7750 0x4008813A:0x3FFB7770 0x40089751:0x3FFB7790 
0x40084a11: esp_crosscore_isr at /home/andrei/esp/esp-idf/components/esp32/crosscore_int.c:77

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400de4fc: esp_task_wdt_reset at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:336

0x400de507: idle_hook_cb at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:88

0x400d57a9: esp_vApplicationIdleHook at /home/andrei/esp/esp-idf/components/esp_common/src/freertos_hooks.c:51 (discriminator 1)

0x4008813a: prvIdleTask at /home/andrei/esp/esp-idf/components/freertos/tasks.c:3839 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3248119) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (3248119) task_wdt:  - IDLE (CPU 0)
E (3248119) task_wdt: Tasks currently running:
E (3248119) task_wdt: CPU 0: Lora
E (3248119) task_wdt: CPU 1: IDLE
E (3248119) task_wdt: Print CPU 0 (current core) backtrace


Backtrace:0x400DE2B8:0x3FFB07F0 0x40082519:0x3FFB0810 0x400D64ED:0x3FFBA1B0 0x40089751:0x3FFBA1D0 
0x400de2b8: task_wdt_isr at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:189

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400d64ed: lmicPingTask at /home/andrei/src/esp32-lora-demo/build/../main/lmic-ping.c:156

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3248119) task_wdt: Print CPU 1 backtrace


Backtrace:0x40084A11:0x3FFB0DF0 0x40082519:0x3FFB0E10 0x4000BFED:0x3FFB76D0 0x400899BE:0x3FFB76E0 0x400DE4FC:0x3FFB7700 0x400DE507:0x3FFB7730 0x400D57A9:0x3FFB7750 0x4008813A:0x3FFB7770 0x40089751:0x3FFB7790 
0x40084a11: esp_crosscore_isr at /home/andrei/esp/esp-idf/components/esp32/crosscore_int.c:77

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400de4fc: esp_task_wdt_reset at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:336

0x400de507: idle_hook_cb at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:88

0x400d57a9: esp_vApplicationIdleHook at /home/andrei/esp/esp-idf/components/esp_common/src/freertos_hooks.c:51 (discriminator 1)

0x4008813a: prvIdleTask at /home/andrei/esp/esp-idf/components/freertos/tasks.c:3839 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3253119) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (3253119) task_wdt:  - IDLE (CPU 0)
E (3253119) task_wdt: Tasks currently running:
E (3253119) task_wdt: CPU 0: Lora
E (3253119) task_wdt: CPU 1: IDLE
E (3253119) task_wdt: Print CPU 0 (current core) backtrace


Backtrace:0x400DE2B8:0x3FFB07F0 0x40082519:0x3FFB0810 0x40089845:0x3FFBA0F0 0x400D9F11:0x3FFBA120 0x400D9F1B:0x3FFBA150 0x400D9F7D:0x3FFBA170 0x400D8CF1:0x3FFBA190 0x400D64F0:0x3FFBA1B0 0x40089751:0x3FFBA1D0 
0x400de2b8: task_wdt_isr at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:189

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x40089845: vPortReleaseTaskMPUSettings at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:364

0x400d9f11: hal_ticks at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:182

0x400d9f1b: delta_time at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:189

0x400d9f7d: hal_checkTimer at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:209

0x400d8cf1: os_runloop_once at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/oslmic.c:113 (discriminator 1)

0x400d64f0: lmicPingTask at /home/andrei/src/esp32-lora-demo/build/../main/lmic-ping.c:158 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3253119) task_wdt: Print CPU 1 backtrace


Backtrace:0x40084A11:0x3FFB0DF0 0x40082519:0x3FFB0E10 0x4000BFED:0x3FFB76D0 0x400899BE:0x3FFB76E0 0x400DE4FC:0x3FFB7700 0x400DE507:0x3FFB7730 0x400D57A9:0x3FFB7750 0x4008813A:0x3FFB7770 0x40089751:0x3FFB7790 
0x40084a11: esp_crosscore_isr at /home/andrei/esp/esp-idf/components/esp32/crosscore_int.c:77

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400de4fc: esp_task_wdt_reset at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:336

0x400de507: idle_hook_cb at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:88

0x400d57a9: esp_vApplicationIdleHook at /home/andrei/esp/esp-idf/components/esp_common/src/freertos_hooks.c:51 (discriminator 1)

0x4008813a: prvIdleTask at /home/andrei/esp/esp-idf/components/freertos/tasks.c:3839 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3258119) task_wdt: Task watchdog got triggered. The following tasks did not reset the watchdog in time:
E (3258119) task_wdt:  - IDLE (CPU 0)
E (3258119) task_wdt: Tasks currently running:
E (3258119) task_wdt: CPU 0: Lora
E (3258119) task_wdt: CPU 1: IDLE
E (3258119) task_wdt: Print CPU 0 (current core) backtrace


Backtrace:0x400DE2B8:0x3FFB07F0 0x40082519:0x3FFB0810 0x4000BFED:0x3FFBA0C0 0x400899BE:0x3FFBA0D0 0x400DDA33:0x3FFBA0F0 0x400D9F11:0x3FFBA120 0x400D9F1B:0x3FFBA150 0x400D9F7D:0x3FFBA170 0x400D8CF1:0x3FFBA190 0x400D64F0:0x3FFBA1B0 0x40089751:0x3FFBA1D0 
0x400de2b8: task_wdt_isr at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:189

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400dda33: vPortExitCriticalSafe at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/include/freertos/portmacro.h:233
 (inlined by) timer_get_counter_value at /home/andrei/esp/esp-idf/components/driver/timer.c:70

0x400d9f11: hal_ticks at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:182

0x400d9f1b: delta_time at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:189

0x400d9f7d: hal_checkTimer at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/hal/hal.c:209

0x400d8cf1: os_runloop_once at /home/andrei/src/esp32-lora-demo/build/../components/lmic-esp-idf/src/lmic/oslmic.c:113 (discriminator 1)

0x400d64f0: lmicPingTask at /home/andrei/src/esp32-lora-demo/build/../main/lmic-ping.c:158 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


E (3258119) task_wdt: Print CPU 1 backtrace


Backtrace:0x40084A11:0x3FFB0DF0 0x40082519:0x3FFB0E10 0x4000BFED:0x3FFB76D0 0x400899BE:0x3FFB76E0 0x400DE4FC:0x3FFB7700 0x400DE507:0x3FFB7730 0x400D57A9:0x3FFB7750 0x4008813A:0x3FFB7770 0x40089751:0x3FFB7790 
0x40084a11: esp_crosscore_isr at /home/andrei/esp/esp-idf/components/esp32/crosscore_int.c:77

0x40082519: _xt_lowint1 at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/xtensa_vectors.S:1105

0x400899be: vPortExitCritical at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:473

0x400de4fc: esp_task_wdt_reset at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:336

0x400de507: idle_hook_cb at /home/andrei/esp/esp-idf/components/esp_common/src/task_wdt.c:88

0x400d57a9: esp_vApplicationIdleHook at /home/andrei/esp/esp-idf/components/esp_common/src/freertos_hooks.c:51 (discriminator 1)

0x4008813a: prvIdleTask at /home/andrei/esp/esp-idf/components/freertos/tasks.c:3839 (discriminator 1)

0x40089751: vPortTaskWrapper at /home/andrei/esp/esp-idf/components/freertos/port/xtensa/port.c:168


device reports readiness to read but returned no data (device disconnected or multiple access on port?)
Waiting for the device to reconnect....................................................................................................................