#include "EPD_4in0e.h"
#include "eink_photo.h"
#include "eink_photo_init.h"
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdio.h>

int main() {
    stdio_init_all();
    sleep_ms(10000);

    repeating_timer_t photo_change_timer;
    if (eink_photo_init()) {
        photo_change_timer_callback(NULL); // First show
        if (!add_repeating_timer_ms(
            7200000, // 2 hours
            photo_change_timer_callback,
            NULL,
                &photo_change_timer)) {
            printf("Failed to add timer to auto change photo\n");
        }
    } else {
        EPD_4IN0E_Init();
        EPD_4IN0E_Clear(EPD_4IN0E_WHITE);
        EPD_4IN0E_Sleep();
    }

    int i = 0;
    while (true) {
        sleep_ms(10000);
    }
}
