#ifndef _DEFINES_H_
#define _DEFINES_H_

#include <stdint.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define EPD_RST_PIN  17
#define EPD_DC_PIN   25
#define EPD_CS_PIN    8
#define EPD_PWR_PIN  18
#define EPD_BUSY_PIN 24
#define EPD_MOSI_PIN 11
#define EPD_CLK_PIN  10

#define SD_SPI_PORT spi1
#define SD_CLK_PIN  30
#define SD_MOSI_PIN 31
#define SD_MISO_PIN 40
#define SD_CS_PIN   43

#endif // _DEFINES_H_
