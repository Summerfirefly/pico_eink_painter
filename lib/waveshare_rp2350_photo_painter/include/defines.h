#ifndef _HW_DEFINE_H_
#define _HW_DEFINE_H_

#include <stdint.h>

/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define EPD_SPI_PORT 	spi1
#define SD_SPI_PORT 	spi0
#define RTC_I2C_PORT    i2c1
#define RTC_I2C_Address 0x51

/**
 * GPIOI config
**/
#define EPD_RST_PIN     12
#define EPD_DC_PIN      8
#define EPD_CS_PIN      9
#define EPD_BUSY_PIN    13
#define EPD_CLK_PIN     10
#define EPD_MOSI_PIN    11
#define EPD_PWR_PIN     16

#define RTC_SDA         14
#define RTC_SCL         15
#define RTC_INT         6

#define CHARGE_STATE    17  // V2
#define BAT_OFF         18
#define BAT_STATE       19

#define LED_ACT         25
#define LED_PWR         26  // V2

#define SD_CS_PIN       5
#define SD_CLK_PIN      2
#define SD_MOSI_PIN     3
#define SD_MISO_PIN     4

#define VBUS            24
#define Power_Mode      23
#define VBAT            29

#endif // _HW_DEFINE_H_
