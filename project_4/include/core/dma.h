#ifndef DMA_H__
#define DMA_H__

extern struct {
	struct {
		volatile unsigned read_addr;
		volatile unsigned write_addr;
		volatile unsigned trans_count;
		volatile unsigned ctrl_trig;
		struct {
			volatile unsigned ctrl;
			volatile unsigned read_addr;
			volatile unsigned write_addr;
			volatile unsigned trans_count_trig;
		} alias[3];

	} channel[12];
	volatile unsigned intr;
	struct {
		volatile unsigned inte;
		volatile unsigned intf;
		volatile unsigned ints;
	} irq[2];
	volatile unsigned timer[4];
	volatile unsigned multi_chan_trigger;
	volatile unsigned sniff_ctrl;
	volatile unsigned fifo_levels;
	volatile unsigned chan_abort;
	volatile unsigned n_channels;
} DMA;
#define DMA_CTRL_DREQ_PIO0_TX0	(0u)

#define DMA_CTRL_TRIG_TREQ_SEL_OFFSET	(15)
#define DMA_CTRL_TRIG_TREQ_SEL_MASK		(0x3fu)
#define DMA_CTRL_RING_SEL			(10)
#define DMA_CTRL_RING_SIZE_OFFSET	(6)
#define DMA_CTRL_RING_SIZE_MASK		(0xfu)
#define DMA_CTRL_INCR_READ			(4)
#define DMA_CTRL_DATA_SIZE_OFFSET	(2)
#define DMA_CTRL_DATA_SIZE_MASK		(0x3u)
#define DMA_CTRL_ENABLE				(0)

#define DMA_CTRL_DATA_SIZE_WORD		(2u)
#define DMA_CTRL_DATA_SIZE_HALFWORD	(1u)
#define DMA_CTRL_DATA_SIZE_BYTE		(0u)

#define DMA_CTRL_RING_SEL_READ		(0u)
#define DMA_CTRL_RING_SEL_WRITE		(1u)

#endif	/* DMA_H__ */
