#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>

#include "clocking.h"
#include "uart0.h"

/* for BAUD computation later on */
//#define BAUD 115200
//#define F_PERIPH 12000000ULL

/* register the UART0 interrupt */
ISR(UART0_vect) {
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

void uart0_init(void) {
	/* initialize clocks */
	//clocking_init();

	/* lift reset out of IO_BANK0 */
	RESETS.reset &= ~(1u << RESETS_reset_io_bank0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_reset_io_bank0);

	/* lift reset on UART0 */
	RESETS.reset &= ~(1u << RESETS_uart0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_uart0);
	
	/* set IO_BANK0 pin function for the TX pin */
	IO_BANK0.io[UART0_TX_GPIO].ctrl = 2;
	IO_BANK0.io[UART0_RX_GPIO].ctrl = 2;


	/* perform BAUD rate computation */
	#include <uart-baud.h>

	/* set up BAUD registers */
	UART0.uartibrd = UARTIBRD_VALUE;
	UART0.uartfbrd = UARTFBRD_VALUE;

	/* and data format */
	UART0.uartlcr_h = (UART_WLEN_8 << UART_LCR_H_WLEN_OFFSET)	/* 8-bit data length */
				;

	/* enable the UART */
	UART0.uartcr =	(1u << UART_CR_UARTEN)	/* enable UART */
				| 	(1u << UART_CR_TXE)		/* enable transmitter */
				|	(1u << UART_CR_RXE)		/* enable reciever */
				;

	/* and the transmit and recieve interrupt */
	UART0.uartimsc = (1u << UART_IMSC_RXIM) | (1u << UART_IMSC_TXIM);

	NVIC_ISER = 1 << NVIC_BIT(UART0_vect);
}
