/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-07-31
* | Info        :
*----------------
* | Modified by :   Summerfirefly (GitHub)
* | Date        :   2026-06-16
* | Info        :
* 1.add:
*   Raspberry Pi Pico/Pico2 Series Support
* 2.Remove:
*   Unused headers and hardware defines
*   Unused functions in this project
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "common_op.h"

#include <hardware/gpio.h>
#include <pico/time.h>
#include "defines.h"

/**
 * GPIO read and write
**/
void DEV_Digital_Write(UWORD Pin, UBYTE Value) {
    gpio_put(Pin, Value != 0);
}

UBYTE DEV_Digital_Read(UWORD Pin) {
    return gpio_get(Pin) ? 1 : 0;
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(UWORD Pin, UWORD Mode) {
    gpio_set_dir(Pin, Mode != 0);
}

/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms) {
    sleep_ms(xms);
}

UBYTE DEV_Module_Init(void)
{
    gpio_init(EPD_BUSY_PIN);
    gpio_init(EPD_RST_PIN);
    gpio_init(EPD_DC_PIN);
    gpio_init(EPD_CS_PIN);
    gpio_init(EPD_PWR_PIN);
    gpio_init(EPD_MOSI_PIN);
    gpio_init(EPD_CLK_PIN);

    gpio_set_dir(EPD_BUSY_PIN, false);
    gpio_set_dir(EPD_RST_PIN, true);
    gpio_set_dir(EPD_DC_PIN, true);
    gpio_set_dir(EPD_CS_PIN, true);
    gpio_set_dir(EPD_PWR_PIN, true);
    gpio_set_dir(EPD_CLK_PIN, true);

    gpio_put(EPD_CS_PIN, true);
    gpio_put(EPD_PWR_PIN, true);

	return 0;
}
