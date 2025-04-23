#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include "spi0.h"


/* register the SPI0 interrupt */
ISR(SPI0_vect) {
	/* message to repeatedly send */
	static const char* const msg = "hello world\r\n";
	/* static storage class means this has permanent store and no external
	 * linkage; since we explicitly initialize this, variable goes in .data */
	static const char* p = msg;
	/* get the character pointed to by p and put it on the transmit buffer;
	 * then increment the pointer */
	UART0.uartdr = *p++;
	if(!*p) {
		/* C strings end in a null terminator; if we are at the terminator then
		 * set the pointer back to the start of the message */
		p = msg;
	}
}

void SPI0_init(void) {

	NVIC_ISER = 1 << NVIC_BIT(SPI0_vect);
}
