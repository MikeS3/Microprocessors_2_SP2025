#include <bitmanip.h>
#include <clocks.h>
#include <ioregs.h>
#include <resets.h>
#include <uart.h>
#include <systick.h>
#include "uart0.h"
#include "spi0.h"
#include <uart-baud.h>
#include "llinit.h"

#if 1
static inline void delay(unsigned n) {
	asm volatile (
		"1:	sub %[r0], #1"	"\n"
		"	bne 1b"
		: [r0]"+r"(n)
		:
		: "memory"
	);
}
#endif
int main(void) {

	low_level_init();
	//INITIALIZE UART and SPI
	uart0_init();
	spi0_init();


	//set SYSTICK upper bound to 12_500_000 for 100ms on 125MHz clock
	SYSTICK.rvr = 12500000;

	SYSTICK.cvr = 0;

	//enable processor clock as systick clock and interrupts when systick reaches 0
	SYSTICK.csr = (TICKINT_OFFSET) | (CLKSOURCE_OFFSET);

	//enable systick
	SYSTICK.csr |= 1;
	

	#define MAX7219_CMD(a, b)  (((a) << 8u) | (b))
	const static unsigned max7219_init[] = {
        MAX7219_CMD(0xc, 0),
        MAX7219_CMD(0xf, 0),
        MAX7219_CMD(0xb, 7),
        MAX7219_CMD(0x9, 0),
        0
    };

	for(const unsigned* p = max7219_init; *p; p++) {
		spi0_send(*p);
	};
	
	for(unsigned i = 1; i < 9; i++) {
		spi0_send(MAX7219_CMD(i, 0));
	};
	
	spi0_send(MAX7219_CMD(0xc, 1));
#if 0
	unsigned char val = 0;
	while(1) {
		spi0_send(MAX7219_CMD(0x1, val));
		val++;
		delay(1000000);
	}
#endif
	return 0;

}
