#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include "spi.h"
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
	SPI0.sspdr = *p++;
}

void spi0_init(void) {

	//Lift Spi out of reset
	RESETS.reset &= ~(1u << RESETS_spi0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_spi0);

		
	//Configure SPI0 for GP6 SCK GP7 TX GP5 CS
	IO_BANK0.io[5].ctrl = 1;
	IO_BANK0.io[6].ctrl = 1;
	IO_BANK0.io[7].ctrl = 1;

	//Set up Device as Master
	//SPI0.sspcr0.SPI_CR0_SCR = (//SPI CLOCK << SPI_CR0_SCR_OFFSET);
	//set the clock prescaler value
	SPI0.sspcpsr = 10;
	SPI0.sspcr0 | SPI_CR0_DSS_MASK; //Enable Data size of 16 bits

	NVIC_ISER = 1 << NVIC_BIT(SPI0_vect);
}
