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


int main(void) {

	low_level_init();
	//INITIALIZE UART and SPI
	uart0_init();
	spi0_init();


	
	return 0;

}
