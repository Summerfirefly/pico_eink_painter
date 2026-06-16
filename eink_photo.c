#include <pico/time.h>
#include <stdio.h>
#include "DEV_Config.h"
#include "pico/stdlib.h"
#include "EPD_4in0e.h"

int main()
{
    stdio_init_all();
    DEV_GPIO_Init();

    EPD_4IN0E_Init();
    EPD_4IN0E_Show7Block();
    EPD_4IN0E_Sleep();

    sleep_ms(300000);

    EPD_4IN0E_Init();
    EPD_4IN0E_Clear(EPD_4IN0E_WHITE);
    EPD_4IN0E_Sleep();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
