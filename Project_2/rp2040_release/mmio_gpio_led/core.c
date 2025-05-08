#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
#include "adc.h"
#include <bitmanip.h>

#include <ioregs.h>

#include <pio.h>



#define GPIO_TRIGGER	(16)

void pio_start(void);
void dma_tx(void);
void low_level_init(void);
void rtc_init(void);
//void adc_init(void);
//void uart0_init(void);

/* dirty software delay loop */
static inline void delay(unsigned n) {

	asm volatile (

		"1:	sub %[r0], #1"	"\n"

		"	bne 1b"

		: [r0]"+r"(n)

		:

		: "memory"

	);

}

//Using GCC macro to take the string of time at compiling, and convert it to numbers
#define HOURS       ((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'))
#define MINUTES(x) ((x[3] - '0') * 10 + (x[4] - '0'))
#define SECONDS     ((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0'))


unsigned current_temp;
int main(void) {
    low_level_init();
    //INITIALIZE UART rtc and SPI
    //uart0_init();
    //adc_init();
    pio_start();
    rtc_init();

    // Set initial time from compile-time macros
    rtc_set_datetime(3, 5, 2025, HOURS, MINUTES(__TIME__), SECONDS);
    
     // Get and print the current time
     unsigned day, month, year, hours, minutes, seconds;
    rtc_get_datetime(&day, &month, &year, &hours, &minutes, &seconds);
   
    // Schedule the first alarm (10 seconds from now)
    //uart0_puts("Scheduling first alarm (10-second interval)...\r\n");
    
    rtc_schedule_next_alarm();
   
    //adc_enable_temp_sensor(1);
    //unsigned current_temp = adc_read(4); // read from Temp adc





	IO_BANK0.io[GPIO_TRIGGER].ctrl = 5;
    SIO.gpio_oe_set = (1u << GPIO_TRIGGER);

while(1) {

    /* trigger signal for oscilloscope debugging */

    SIO.gpio_out_clr = (1u << GPIO_TRIGGER);
    SIO.gpio_out_set = (1u << GPIO_TRIGGER);

    /* start the DMA transfer */

    dma_tx();
    /* and delay stuff */
    delay(250000);

}
    return 0;
}