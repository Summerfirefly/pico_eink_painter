#include "eink_photo.h"

#include <pico/rand.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "EPD_4in0e.h"
#include "ff.h"
#include "ffconf.h"

static int total_photo_num = -1;
static char picked_photo[FF_LFN_BUF + 1] = {0};

bool photo_change_timer_callback(repeating_timer_t *rt) {
    pick_next_photo();
    show_photo();
    return true;
}

void pick_next_photo(void) {
    if (total_photo_num < 0) {
        scan_photo();
    }

    picked_photo[0] = '\0';
    if (total_photo_num <= 0) {
        return;
    }

    int index = get_rand_32() % total_photo_num;
    printf("Pick photo index: %d\n", index);
    DIR dir;
    if (f_opendir(&dir, ".") == FR_OK) {
        FILINFO fileinfo;
        int i = 0;
        while (true) {
            f_readdir(&dir, &fileinfo);
            if (fileinfo.fname[0] == '\0') {
                break;
            } else if (fileinfo.fattrib & AM_DIR) {
                continue;
            } else if (strstr(fileinfo.fname, ".bin") != NULL) {
                if (i == index) {
                    strlcpy(picked_photo, fileinfo.fname, sizeof(picked_photo));
                    break;
                }

                ++i;
            }
        }
    }

    f_closedir(&dir);
    printf("Picked: %s\n", picked_photo);
}

void show_photo(void) {
    printf("Show photo: %s\n", picked_photo);
    if (strlen(picked_photo) > 0) {
        FIL file;
        if (f_open(&file, picked_photo, FA_READ) != FR_OK) {
            printf("Failed to open file: %s\n", picked_photo);
        } else {
            uint8_t buffer[EPD_4IN0E_WIDTH * 50];
            UINT read_bytes, total_read = 0;
            EPD_4IN0E_Init();
            EPD_4IN0E_StartImageSend();
            do {
                read_bytes = 0;
                if (f_read(&file, buffer, sizeof(buffer), &read_bytes) != FR_OK) {
                    printf("Failed to read file at byte %u: %s\n", total_read + read_bytes, picked_photo);
                    break;
                } else {
                    total_read += read_bytes;
                    EPD_4IN0E_SendImageData(buffer, read_bytes);
                }
            } while (read_bytes == sizeof(buffer));

            f_close(&file);
            EPD_4IN0E_EndImageSend();
            EPD_4IN0E_Sleep();
        }
    }
}

static void scan_photo(void) {
    printf("Scan photo...\n");
    DIR dir;
    total_photo_num = 0;
    if (f_opendir(&dir, ".") == FR_OK) {
        FILINFO fileinfo;
        while (true) {
            f_readdir(&dir, &fileinfo);
            printf("Checking %s\n", fileinfo.fname);
            if (fileinfo.fname[0] == '\0') {
                break;
            } else if (fileinfo.fattrib & AM_DIR) {
                continue;
            } else if (strstr(fileinfo.fname, ".bin") != NULL) {
                total_photo_num++;
            }
        }
    }

    f_closedir(&dir);
    printf("Total photo num: %d\n", total_photo_num);
}
