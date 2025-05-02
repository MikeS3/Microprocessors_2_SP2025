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

extern void low_level_init(void);
extern void uart0_init(void);
extern void uart0_puts(const char *s);
extern void uart0_putchar(char c);

// Move uart0_putnum function outside of the while loop
void uart0_putnum(unsigned val) {
    char digits[10];
    int i = 0;
 
    if (val == 0) {
        uart0_puts("0");
        return;
    }
 
    while (val > 0 && i < 10) {
        digits[i++] = '0' + (val % 10);
        val /= 10;
    }
 
    for (int j = i - 1; j >= 0; --j) {
        uart0_putchar(digits[j]);
    }
}

int main(void) {
    low_level_init();
    //INITIALIZE UART rtc and SPI
    uart0_init();
    //spi0_init();
    uart0_puts("RTC INIT\n");
    rtc_init();
    rtc_set_datetime(30, 4, 2025, 10, 45, 0);

    //enable systick
    SYSTICK.csr |= 1;
    //enable systick interrupt:
    SYSTICK.csr |= TICKINT_OFFSET;

    while (1) {
        unsigned d, m, y, h, min, s;
        rtc_get_datetime(&d, &m, &y, &h, &min, &s);
        
        // Print datetime in format: DD/MM/YYYY HH:MM:SS
        uart0_putnum(d);
        uart0_putchar('/');
        uart0_putnum(m);
        uart0_putchar('/');
        uart0_putnum(y);
        uart0_putchar(' ');
        uart0_putnum(h);
        uart0_putchar(':');
        uart0_putnum(min);
        uart0_putchar(':');
        uart0_putnum(s);
        uart0_puts("\r\n");

        // Crude delay
        for (volatile int i = 0; i < 1000000; ++i);
    }

    return 0;
}