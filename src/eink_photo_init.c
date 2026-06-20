#include "eink_photo_init.h"

#include <hardware/gpio.h>
#include "common_op.h"
#include "ff.h"

static FATFS fs;

bool eink_photo_init(void) {
    return (DEV_Module_Init() == 0) && fatfs_init();
}

static bool fatfs_init(void) {
    if (f_mount(&fs, "", 1) == FR_OK) {
        f_chdir("/photo_data");
        return true;
    }

    return false;
}
