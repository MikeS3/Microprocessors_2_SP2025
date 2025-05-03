#include <bitmanip.h>
#include <clocks.h>
#include <ioregs.h>
#include <resets.h>
#include "uart0.h"
#include "rtc.h"
#include "pio.h"
#include <uart-baud.h>
#include <uart.h>
#include <systick.h>
#include "llinit.h"


int main(void) {
    low_level_init();
    //INITIALIZE UART rtc and SPI
    uart0_init();
    //spi0_init();
    rtc_init();
    adc_init();
    rtc_set_datetime(3, 5, 2025, 10, 45, 0);

    return 0;
}