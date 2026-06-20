#include "eink_photo_init.h"

#include <hardware/gpio.h>
#include "DEV_Config.h"
#include "ff.h"

static FATFS fs;

bool eink_photo_init(void) {
    return epaper_pin_init() && fatfs_init();
}

static bool epaper_pin_init(void) {
    EPD_RST_PIN     = 17;
    EPD_DC_PIN      = 25;
    EPD_CS_PIN      = 8;
    EPD_PWR_PIN     = 18;
    EPD_BUSY_PIN    = 24;
    EPD_MOSI_PIN    = 11;
    EPD_SCLK_PIN    = 10;

    gpio_init(EPD_BUSY_PIN);
    gpio_init(EPD_RST_PIN);
    gpio_init(EPD_DC_PIN);
    gpio_init(EPD_CS_PIN);
    gpio_init(EPD_PWR_PIN);
    gpio_init(EPD_MOSI_PIN);
    gpio_init(EPD_SCLK_PIN);

    gpio_set_dir(EPD_BUSY_PIN, false);
    gpio_set_dir(EPD_RST_PIN, true);
    gpio_set_dir(EPD_DC_PIN, true);
    gpio_set_dir(EPD_CS_PIN, true);
    gpio_set_dir(EPD_PWR_PIN, true);
    gpio_set_dir(EPD_SCLK_PIN, true);

    gpio_put(EPD_CS_PIN, true);
    gpio_put(EPD_PWR_PIN, true);

    return true;
}

static bool fatfs_init(void) {
    if (f_mount(&fs, "", 1) == FR_OK) {
        f_chdir("/photo_data");
        return true;
    }

    return false;
}
