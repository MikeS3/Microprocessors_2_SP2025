#include <bitmanip.h>

#include <clocks.h>

#include <ioregs.h>

#include <resets.h>
#include "uart0.h"

#include <uart-baud.h>
#include <uart.h>
#include "llinit.c"



int main(void) {

	low_level_init();

	//Configure UART0 for GP0 TX GP1 RX
	IO_BANK0.io[0].ctrl = 2;
	IO_BANK0.io[1].ctrl = 2;

	//INITIALIZE UART AND SEND MESSAGE
	uart0_init();


	//Configure SPI0 for GP6 SCK GP7 TX GP5 CS
	IO_BANK0.io[5].ctrl = 1;
    IO_BANK0.io[6].ctrl = 1;
	IO_BANK0.io[7].ctrl = 1;

	return 0;

}
