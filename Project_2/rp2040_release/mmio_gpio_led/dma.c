#include <dma.h>
#include <pio.h>

__attribute__((constructor(105)))
void dma_init(void) {
	DMA.channel[0].write_addr = &PIO0.txf[0];	/* write to TXF0 on PIO0 */
	DMA.channel[0].trans_count = 16;			/* data count */
	DMA.channel[0].ctrl_trig =
			/* use TX0 from PIO0 as the data request channel */
			(DMA_CTRL_DREQ_PIO0_TX0 << DMA_CTRL_TRIG_TREQ_SEL_OFFSET)
			/* use 32 bit words as the read/write size */
		|	(DMA_CTRL_DATA_SIZE_WORD << DMA_CTRL_DATA_SIZE_OFFSET)
			/* increment reads */
		|	(1u << DMA_CTRL_INCR_READ)
			/* wrap on 64 bit addresses */
		|	(6u	<< DMA_CTRL_RING_SIZE_OFFSET)
			/* on the read channel */
		|	(DMA_CTRL_RING_SEL_READ << DMA_CTRL_RING_SEL)
		;
}

static const unsigned dma_data[] __attribute__((aligned(64))) = {
		0x00ff0000u,
		0x80ff0000u,
		0xffff0000u,
		0xff800000u,
		0xff000000u,
		0xff008000u,
		0xff00ff00u,
		0x8000ff00u,
		0x0000ff00u,
		0x0080ff00u,
		0x00ffff00u,
		0x00ff8000u,
		0x00000000u,
		0x00000000u,
		0x00000000u,
		0x00000000u
	};

void dma_tx(void) {
	static short offset;
	/* set the read address */
	DMA.channel[0].read_addr = dma_data + offset;
	/* and enable the channel */
	DMA.channel[0].ctrl_trig |= (1u << DMA_CTRL_ENABLE);
	offset++;
	offset &= 0xf;
}
