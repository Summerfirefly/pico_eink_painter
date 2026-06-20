#ifndef _PP_RTC_H_
#define _PP_RTC_H_

#include <stdint.h>

void rtc_write_byte(uint8_t reg, uint8_t value);
uint8_t rtc_read_byte(uint8_t reg);

#endif // _PP_RTC_H_
