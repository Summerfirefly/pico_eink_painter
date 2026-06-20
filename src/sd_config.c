#include <hardware/spi.h>
#include <hw_config.h>

#include "defines.h"

static spi_t spi = {
    .hw_inst = SD_SPI_PORT,
    .baud_rate = 125 * 1000 * 1000 / 4,
    .sck_gpio = SD_CLK_PIN,
    .mosi_gpio = SD_MOSI_PIN,
    .miso_gpio = SD_MISO_PIN
};

static sd_spi_if_t sd_spi_if = {
    .spi = &spi,
    .ss_gpio = SD_CS_PIN
};

static sd_card_t sd_card = {
    .type = SD_IF_SPI,
    .spi_if_p = &sd_spi_if
};

size_t sd_get_num() {
    return 1;
}

sd_card_t* sd_get_by_num(size_t num) {
    if (num == 0) {
        return &sd_card;
    }

    return NULL;
}
