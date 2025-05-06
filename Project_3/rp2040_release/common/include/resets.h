#ifndef RESETS_H__
#define RESETS_H__

extern struct {
	volatile unsigned reset;
	volatile unsigned wdsel;
	volatile unsigned reset_done;
} RESETS;

/* RESETS */
#define RESETS_reset_io_bank0		(5)
#define RESETS_reset_done_io_bank0	(5)
#define RESETS_pll_sys				(12)
#define RESETS_uart0				(22)
#define RESETS_spi0			(16)
#define RESETS_spi1			(17)
#define RESETS_pio0			(10)
#define RESETS_pio1			(11)
#define RESETS_rtc			(15)
#define RESETS_i2c1			(4)
#define RESETS_i2c0			(3)
#define RESETS_dma			(2)
#define RESETS_adc			(0)



#endif	/* RESETS_H__ */