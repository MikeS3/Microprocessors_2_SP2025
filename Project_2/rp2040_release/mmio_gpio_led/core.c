#include <bitmanip.h>
#include <clocks.h>
#include <ioregs.h>
#include <resets.h>
#include "uart0.h"
#include "spi0.h"
#include "pio.h"
#include <uart-baud.h>
#include <uart.h>
#include <systick.h>
#include "llinit.h"

#define MAX7219_CMD(a, b)  (((a) << 8u) | (b))

int main(void) {

	low_level_init();
	//INITIALIZE UART and SPI
	//uart0_init();
	//spi0_init();
	



	//enable systick
	SYSTICK.csr |= 1;
	//enable systick interrupt:
	SYSTICK.csr |= TICKINT_OFFSET;


	return 0;

}
