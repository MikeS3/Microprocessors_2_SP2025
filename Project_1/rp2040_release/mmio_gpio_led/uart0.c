#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>
#include "uart0.h"
#include "image.h"

/* register the UART0 interrupt */
ISR(UART0_vect) {
    static unsigned char checksum;
    // static enum { idle, size_1, size_2, data, checksum } state;
    static unsigned short index = 0;  // Index to track position in the frame
    static unsigned char image_index = 0;  // Which image buffer to use (0 or 1)
    
    unsigned char byte = UART0.uartdr;
    
    // Process byte based on index position in the frame
    switch(index) {
        case 0:  // Start byte
            if(byte == 0x46) {  // Check for start byte (0x46)
                checksum = byte;  // Reset and initialize checksum with start byte
                img[image_index].index = 0;  // Reset data index
                index++;          // Move to next byte
            }

			break;
            
        case 1:  // Length MSB
            img[image_index].size = byte << 8;  // Store MSB of length
            checksum += byte;    // Add to checksum
            index++;             // Move to next byte
            break;
            
        case 2:  // Length LSB
            img[image_index].size |= byte;      // Store LSB of length
            img[image_index].size += 1;         // Adjust length (payload size minus one)
            checksum += byte;    // Add to checksum
            index++;             // Move to next byte (start of data)
            break;
            
        default:
            // Data or checksum bytes
            if(index < (img[image_index].size + 3)) {  // Data bytes (offset 3 to length+2)
                // Store data byte in the image structure
                img[image_index].data[index - 3] = byte;  // Adjust index to start at 0 for buffer
                checksum += byte;                        // Add to checksum
            } else if(index == (img[image_index].size + 3)) {  // Checksum byte
                // Verify checksum
                if((byte + checksum) == 0) {
                    // Checksum matches, frame is valid
                                        
                } else {
                    // Checksum error handling
                    
                }
                
                // Reset index for next frame regardless of checksum result
                index = 0;
                break;
            }
            
            index++;  // Move to next byte
            break;
    }
    
    // Safety check - if we somehow get an invalid index, reset to 0
    if(index > (img[image_index].size + 3) && index > 3) {
        index = 0;
    }
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
