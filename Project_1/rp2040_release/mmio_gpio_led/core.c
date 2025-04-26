#include <bitmanip.h>
#include <clocks.h>
#include <ioregs.h>
#include <resets.h>
#include "uart0.h"
#include "spi0.h"
#include <uart-baud.h>
#include <uart.h>
#include <systick.h>
#include "llinit.h"

#define MAX7219_CMD(a, b)  (((a) << 8u) | (b))

int main(void) {

	low_level_init();
	//INITIALIZE UART and SPI
	uart0_init();
	spi0_init();

	//enable systick
	SYSTICK.csr |= 1;
	//enable systick interrupt:
	SYST.csr |= TICKINT_OFFSET;

	/*
	const static unsigned max7219_init[] = {
        MAX7219_CMD(0xc, 0),
        MAX7219_CMD(0xf, 0),
        MAX7219_CMD(0xb, 7),
        MAX7219_CMD(0x9, 0),
        0
    };

	for(const unsigned* p = max7219_init, *p, p++) {
		spi_send(*p);
	}
	
	for(unsigned i = 1; i < 9; i++) {
		spi_send(MAX7219_CMD(i, 0));
	}
	
	spi_send(MAX7219_CMD(0xc, 1));
	*/

	return 0;

}
