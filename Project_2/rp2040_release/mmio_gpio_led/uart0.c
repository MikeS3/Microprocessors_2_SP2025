#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>
#include "uart0.h"
//#include "image.h"

/* register the UART0 interrupt */
ISR(UART0_vect) {
    static unsigned char checksum;
    // static enum { idle, size_1, size_2, data, checksum } state;
    static unsigned short index = 0;  // Index to track position in the frame
    static unsigned char image_index = 0;  // Which image buffer to use (0 or 1)
    
    unsigned char byte = UART0.uartdr;
    
    // Process byte based on index position in the frame
    
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
				|	(1u << UART_CR_TXE)		/* enable transmitter */
				|	(1u << UART_CR_RXE)		/* enable reciever */
				;

	/* and the transmit and recieve interrupt */
	UART0.uartimsc = (1u << UART_IMSC_RXIM); //| (1u << UART_IMSC_TXIM);

	NVIC_ISER = 1 << NVIC_BIT(UART0_vect);
}
void uart0_putc(char c) {
    // Wait until there is space in the FIFO
    while (UART0.uartfr & UART_FR_TXFF);
    
    // Write the character to the data register
    UART0.uartdr = c;
}

// Function to send a string
void uart0_puts(const char *str) {
    while (*str) {
        // Handle newline by sending CR+LF
        if (*str == '\n') {
            uart0_putc('\r');
        }
        uart0_putc(*str++);
    }
}

// Function to check if there is data to read
int uart0_rx_ready(void) {
    return !(UART0.uartfr & UART_FR_RXFE);
}

// Function to read a character
char uart0_getc(void) {
    // Wait until there is data to read
    while (UART0.uartfr & UART_FR_RXFE);
    
    // Read and return the received character
    return (char)(UART0.uartdr & 0xFF);
}