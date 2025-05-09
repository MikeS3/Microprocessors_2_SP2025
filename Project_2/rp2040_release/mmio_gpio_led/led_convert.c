#include <string.h>
#include "dma.h"
#include "pio.h"  
unsigned adc_read(void);
const static unsigned color_table[16] = {
	0x0000FF,  // Blue (coldest)
    0x0033FF,  
    0x0066FF,  
    0x0099FF,  
    0x00CCFF,  
    0x00FFCC,  
    0x00FF99,  
    0x00FF66,  
    0x00FF33,  
    0x33FF00,  
    0x66FF00,  
    0x99FF00,  
    0xCCFF00,  
    0xFF9900,  
    0xFF6600,  
    0xFF0000   // (hottest)
	};

static unsigned led_array_data[16];

void show_temperature(void) {
	unsigned short led_total;
	unsigned raw_adc_value = adc_read();
	if(adc_raw_value > 967) {
		led_total = 1;
	} else if(adc_raw_value > 958) {
		led_total = 2;
	} else if(adc_raw_value > 949) {
		led_total = 3;
	} else if(adc_raw_value > 939) {
		led_total = 4;
	} else if(adc_raw_value > 930) {
		led_total = 5;
	} else if(adc_raw_value > 921) {
		led_total = 6;
	} else if(adc_raw_value > 911) {
		led_total = 7;
	} else if(adc_raw_value > 902) {
		led_total = 8;
	} else if(adc_raw_value > 893) {
		led_total = 9;
	} else if(adc_raw_value > 883) {
		led_total = 10;
	} else if(adc_raw_value > 874) {
		led_total = 11;
	} else if(adc_raw_value > 865) {
		led_total = 12;
	} else if(adc_raw_value > 855) {
		led_total = 13;
	} else if(adc_raw_value > 846) {
		led_total = 14;
	} else if(adc_raw_value > 837) {
		led_total = 15;
	} else {
		led_total = 16;
	}
	memcpy(led_array_data, color_table, led_total * sizeof(led_array_data[0]));
	if(led_total < 16) {
		memset(led_array_data + led_total, 0, sizeof(led_array_data[0]) * (16 - led_total));
	}

	/* TODO: set DMA read register on channel 0 to address of led_array_data */
	DMA.channel[0].read_addr = (unsigned)&led_array_data[0];
	DMA.channel[0].trans_count = 16;

	DMA.channel[0].ctrl_trig =
		(DMA_CTRL_DATA_SIZE_WORD << DMA_CTRL_DATA_SIZE_OFFSET) | // 32-bit transfer
		(1 << DMA_CTRL_INCR_READ) |                               // incremeent read ad#
		(DMA_CTRL_DREQ_PIO0_TX0 << DMA_CTRL_TRIG_TREQ_SEL_OFFSET) |
		(1 << DMA_CTRL_ENABLE);                                   // start DMA
}	/* TODO: start DMA transfer */

