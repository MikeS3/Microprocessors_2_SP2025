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
    uart0_init();
    //spi0_init();
    rtc_init();
    adc_init();
    rtc_set_datetime(3, 5, 2025, HOURS, MINUTES(__TIME__), SECONDS);
    unsigned current_temp = adc_read(4); // read from Temp adc
    pio_start();



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