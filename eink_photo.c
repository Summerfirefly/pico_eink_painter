#include <pico/stdio.h>
#include <pico/time.h>
#include <stdio.h>
#include "demo/demo_func.h"

int main()
{
    stdio_init_all();

    sleep_ms(30000); // Wait some time for user to open serial monitor
    demo_sd_print_file("/hello.txt");
    demo_epaper();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(5000);
    }
}
