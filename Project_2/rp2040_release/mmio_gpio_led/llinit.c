//wite to ttyACM0 for CMSIS it is uart bridge from pc to pi. USING python file
//SPI Setup is similar

#include <bitmanip.h>

#include <clocks.h>

#include <ioregs.h>

#include <resets.h>
#include "uart0.h"
#include "dma.h"

#include <uart.h>

void start_unresets(void) {

	/* lift IO_BANK0 out of reset */

	RESETS.reset &= ~(1u << RESETS_reset_io_bank0);


	/*lift UART0 out of reset*/

	RESETS.reset &= ~(1u << RESETS_uart0);


	/*lift SPI0 out of reset*/

    //RESETS.reset &= ~(1u << RESETS_spi0);

	/* lift system PLL out of reset */
	RESETS.reset &= ~(1u << RESETS_pll_sys);

	//lift pio out of reset
	RESETS.reset &= ~(1 << RESETS_pio0);

	//lift I2C0 out of RESET
	//RESETS.reset &= ~(1 << RESETS_i2c0);
	//lift rtc out of reset
	RESETS.reset &= ~(1 << RESETS_rtc);

	/* lift DMA out of reset */
	RESETS.reset &= ~(1 << RESETS_dma);

	/* lift ADC out of reset */
	RESETS.reset &= ~(1 << RESETS_adc);



}
void finish_unresets(void) {

	loop_until_bit_is_set(RESETS.reset_done, RESETS_reset_io_bank0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_uart0);
	//loop_until_bit_is_set(RESETS.reset_done, RESETS_spi0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_pll_sys);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_pio0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_rtc);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_dma);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_adc);
	//loop_until_bit_is_set(RESETS.reset_done, RESETS_i2c0);
	//RESETS.reset &= ~(1 << RESETS_i2c1);



}

void clocks_init(void)
{
	/* enable the external oscillator */
	XOSC.ctrl = XOSC_enable | XOSC_freq_range_1_15MHz;
	loop_until_bit_is_set(XOSC.status, XOSC_stable);
	//Enable Peripheral Clock and set to XOSC
	CLOCKS.clk_peri_ctrl = (1u << CLOCKS_enable) | (CLOCKS_PERI_xosc_clksrc);
	CLOCKS.clk_adc_ctrl = (1u << CLOCKS_enable) | (CLOCKS_ADC_clk_clksrc_pll_usb);
	CLOCKS.clk_rtc_ctrl = (1u << CLOCKS_enable) | (CLOCKS_RTC_xosc_clksrc);

	/** switch system clock to XOSC */
	/* first set the clock to use the reference clock */
	CLOCKS.clk_sys_ctrl &= ~(1 << CLOCKS_SYS_CTRL_SRC);
	loop_until_bit_is_set(CLOCKS.clk_sys_selected, 0);

	/* then set the aux multiplexer */
	CLOCKS.clk_sys_ctrl =
			(CLOCKS_SYS_CTRL_XOSC_CLKSRC << CLOCKS_SYS_CTRL_AUXSRC_OFFSET);
	/* then set the glitchless mux */
	CLOCKS.clk_sys_ctrl |= (CLOCKS_SYS_CTRL_CLKSRC_CLK_SYS_AUX);
	/* and wait for it to settle */
	loop_until_bit_is_set(CLOCKS.clk_sys_selected, 1);

}

void low_level_init(void)
{
	start_unresets();
	clocks_init();
	//Peripheral clock must be set before UART is reset
	finish_unresets();
}
