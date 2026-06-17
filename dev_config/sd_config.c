#include <hardware/spi.h>
#include <hw_config.h>

static spi_t spi = {
    .hw_inst = spi1,
    .baud_rate = 125 * 1000 * 1000 / 4,
    .sck_gpio = 30,
    .mosi_gpio = 31,
    .miso_gpio = 40
};

static sd_spi_if_t sd_spi_if = {
    .spi = &spi,
    .ss_gpio = 43
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
