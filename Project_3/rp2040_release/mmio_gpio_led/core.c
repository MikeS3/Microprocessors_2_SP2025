#include <bitmanip.h>
#include <clocks.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>
#include <systick.h>
#include "uart0.h"
#include "spi0.h"
#include <uart-baud.h>
#include "llinit.h"

#define MAX7219_CMD(a, b)  (((a) << 8u) | (b))

int main(void) {

	low_level_init();
	//INITIALIZE UART and SPI
	uart0_init();
	spi0_init();


	//enable systick interrupt:
	SYSTICK.csr = (1 << TICKINT_OFFSET) | (1 << CLKSOURCE_OFFSET);
	//set SYSTICK upper bound to 1_200_000 for 100ms on 12MHz clock
	SYSTICK.rvr = 1200000;
	//enable systick
	SYSTICK.csr |= 1;
	
	return 0;

}
