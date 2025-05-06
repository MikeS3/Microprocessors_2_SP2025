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
    adc_init();


	SIO. = (1u << GPIO_TRIGGER);
    return 0;
}