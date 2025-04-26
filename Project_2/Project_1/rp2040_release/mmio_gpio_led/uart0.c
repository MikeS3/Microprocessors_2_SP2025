#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>
#include "uart0.h"

/* register the UART0 interrupt */
ISR(UART0_vect) {
	static unsigned char checksum;
	unsigned char byte = UART0.uartdr;
	//UART state machine

	if(byte = 0x46) {
		checksum = 0;
	}
	/* Run checksum to make sure data is valid */

	//Set SPI0_vect Pending
	//NVIC_ISPR = 1 << NVIC_BIT(SPI0_vect);
}

void uart0_init(void) {

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
				/*| 	(1u << UART_CR_TXE)*/		/* enable transmitter */
				|	(1u << UART_CR_RXE)		/* enable reciever */
				;

	/* and the transmit and recieve interrupt */
	UART0.uartimsc = (1u << UART_IMSC_RXIM); //| (1u << UART_IMSC_TXIM);

	NVIC_ISER = 1 << NVIC_BIT(UART0_vect);
}
