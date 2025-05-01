#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <spi.h>
#include "spi0.h"
#include "image.h"

/* register the SPI0 interrupt */
ISR(SPI0_vect) {
	//SPI0.sspdr = img[0].data[img[0].index];
	spi0_send(img[0].data[img[0].index])
	
}

void spi0_init(void) {

	//Lift Spi out of reset
	RESETS.reset &= ~(1u << RESETS_spi0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_spi0);

		
	//Configure SPI0 for GP6 SCK GP7 TX GP5 CS
	IO_BANK0.io[5].ctrl = 1;
	IO_BANK0.io[6].ctrl = 1;
	IO_BANK0.io[7].ctrl = 1;

	//SPI0.sspcr0.SPI_CR0_SCR = (//SPI CLOCK << SPI_CR0_SCR_OFFSET);
	//set the clock prescaler value
	SPI0.sspcpsr = 10;
	SPI0.sspcr0 |= SPI_CR0_DSS_16; //Enable Data size of 16 bits
	SPI0.sspcr1 &= ~(SPI_CR1_MS); // set device as master
	SPI0.sspcr1 |= SPI_CR1_SSE;
}

void spi0_send(unsigned short message){
	//pull chip select high
	//IO_BANK0.io[5].crtl |= (0x3 << 8);
	//send data
	SPI0.sspdr = message;
}
/*
#define MAX7219_CMD(a, b)  (((a) << 8u) | (b))
const static unsigned max7219_init[] = {
        MAX7219_CMD(0xc, 0),
        MAX7219_CMD(0xf, 0),
        MAX7219_CMD(0xb, 7),
        MAX7219_CMD(0x9, 0),
        0
    };

/* initialize SPI somewhere, then assuming a function with prototype */
/* void spi_send(unsigned) 
for(const unsigned* p = max7219_init, *p, p++) {
    spi_send(*p);
}

for(unsigned i = 1; i < 9; i++) {
    spi_send(MAX7219_CMD(i, 0));
}

spi_send(MAX7219_CMD(0xc, 1));
*/