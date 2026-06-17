#include "demo_func.h"

#include <pico/time.h>
#include <stdio.h>
#include "DEV_Config.h"
#include "EPD_4in0e.h"
#include "ff.h"

void demo_epaper(void) {
    DEV_GPIO_Init();

    EPD_4IN0E_Init();
    EPD_4IN0E_Show7Block();
    EPD_4IN0E_Sleep();

    sleep_ms(300000);

    EPD_4IN0E_Init();
    EPD_4IN0E_Clear(EPD_4IN0E_WHITE);
    EPD_4IN0E_Sleep();
}

void demo_sd_print_file(const char *filepath) {
    FATFS fatfs;
    if (f_mount(&fatfs, "", 1) != FR_OK) {
        printf("Failed to mount SD card\n");
    } else {
        FIL file;
        const char *filepath = "/hello.txt";
        if (f_open(&file, filepath, FA_READ) != FR_OK) {
            printf("Failed to open file: %s\n", filepath);
        } else {
            char buffer[512];
            UINT read_bytes, total_read = 0;
            do {
                read_bytes = 0;
                if (f_read(&file, buffer, sizeof(buffer) - 1, &read_bytes) != FR_OK) {
                    printf("Failed to read file at byte %u: %s\n", total_read + read_bytes, filepath);
                    break;
                } else {
                    total_read += read_bytes;
                    buffer[read_bytes] = '\0';
                    printf("%s", buffer);
                }
            } while (read_bytes == sizeof(buffer) - 1);

            f_close(&file);
        }

        f_unmount("");
    }
}
