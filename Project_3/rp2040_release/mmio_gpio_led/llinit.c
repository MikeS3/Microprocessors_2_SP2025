//wite to ttyACM0 for CMSIS it is uart bridge from pc to pi. USING python file
//SPI Setup is similar

#include <bitmanip.h>

#include <clocks.h>

#include <ioregs.h>

#include <resets.h>
#include "uart0.h"
#include <uart.h>

void start_unresets(void) {

	/* lift IO_BANK0 out of reset */

	RESETS.reset &= ~(1u << RESETS_reset_io_bank0);


	/*lift UART0 out of reset*/

	RESETS.reset &= ~(1u << RESETS_uart0);


	/*lift SPI0 out of reset*/

    RESETS.reset &= ~(1u << RESETS_spi0);


	/* lift system PLL out of reset */

	RESETS.reset &= ~(1u << RESETS_pll_sys);


}
void finish_unresets(void) {

	loop_until_bit_is_set(RESETS.reset_done, RESETS_reset_io_bank0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_uart0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_spi0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_pll_sys);


}

void clocks_init(void)
{
	/* enable the external oscillator */
	XOSC.ctrl = XOSC_enable | XOSC_freq_range_1_15MHz;
	loop_until_bit_is_set(XOSC.status, XOSC_stable);
	//Enable Peripheral Clock and set to XOSC
	CLOCKS.clk_peri_ctrl = (1u << CLOCKS_enable) | (CLOCKS_PERI_xosc_clksrc);

}

void low_level_init(void)
{
	start_unresets();
	clocks_init();
	//Peripheral clock must be set before UART is reset
	finish_unresets();
}
