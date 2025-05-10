#include <stddef.h>

#include "pio.h"
#include "dma.h"
extern unsigned pio_data[16];

int svc_setring(unsigned* data, size_t count) {
//#	warning "function must be implemented\n" 

		//"- if DMA is active for the PIO then return -1\n"	
		//"- if count is greater than 16 then return -2\n" 
		//"- otherwise, copy from data into pio_data, setup DMA and fire away"
	/* notice: shift every piece of data by 8 bits to the left as you store it
	 * in the buffer! */
	 // 1) If DMA channel 0 is active, return -1
    #if 0
	 if (DMA.channel[0].ctrl_trig & (1u << DMA_CTRL_ENABLE)) {
        return -1;
    }

    // 2) If count > 16, return -2
    if (count > 16) {
        return -2;
    }

    // 3) Otherwise, copy data into pio_data, shifting each word left by 8 bits
    for (size_t i = 0; i < count; ++i) {
        pio_data[i] = data[i] << 8;
    }
    // Zero out the rest of the buffer
    for (size_t i = count; i < 16; ++i) {
        pio_data[i] = 0;
    }

	//DMA channel 0
    DMA.channel[0].read_addr   = (unsigned)pio_data;
    DMA.channel[0].write_addr  = (unsigned)&PIO0.txf[0];
    DMA.channel[0].trans_count = count;

    DMA.channel[0].ctrl_trig =
          (DMA_CTRL_DATA_SIZE_WORD << DMA_CTRL_DATA_SIZE_OFFSET)    // 32-bit
        | (1u << DMA_CTRL_INCR_READ)                               // inc read
        | (0u << 5)                                                // no write inc
        | (DMA_CTRL_DREQ_PIO0_TX0 << DMA_CTRL_TRIG_TREQ_SEL_OFFSET) // pacing by PIO
        | (1u << DMA_CTRL_ENABLE);                                 // go
	#endif
    return 0;
}

