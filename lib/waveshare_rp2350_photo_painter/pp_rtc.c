#include "pp_rtc.h"

#include <hardware/i2c.h>
#include "defines.h"

void rtc_write_byte(uint8_t reg, uint8_t value) {
	uint8_t wbuff[2] = {reg, value};
	i2c_write_blocking(RTC_I2C_PORT, RTC_I2C_Address, wbuff, 2, false);
}

uint8_t rtc_read_byte(uint8_t reg) {
	uint8_t value;
	i2c_write_blocking(RTC_I2C_PORT, RTC_I2C_Address, &reg, 1, false);
	i2c_read_blocking(RTC_I2C_PORT, RTC_I2C_Address, &value, 1, false);
	return value;
}
