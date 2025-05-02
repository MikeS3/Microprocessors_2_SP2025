#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>
#include <spi.h>
#include "spi0.h"
#include "image.h"

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


/* register the SPI0 interrupt */
ISR(SPI0_vect) {
	//SPI0.sspdr = img[0].data[img[0].index];
	static int total_sent;
	unsigned char column_data;
	int local_index = 0;
	for(total_sent = 0; total_sent < 8; total_sent++)
	{
		local_index = total_sent;
		if((img[current_image].index + total_sent) >= img[current_image].size)
		{
			local_index = img[current_image].index + total_sent - img[current_image].size;
		}
	column_data = img[current_image].data[local_index];
	
	//MAX7219_CMD(0x1, column_data);
	spi0_send(((total_sent) << 8u) | (column_data));
	//NVIC_ICPR = 1 << NVIC_BIT(SPI0_vect); //clear interrupt pending register
	}

	//after 8 sent, clear ISER
	NVIC_ICER = 1 << NVIC_BIT(SPI0_vect); //clear interrupt pending register

	//ISCR clear
	//after 8 sent, clear ICPR
}

