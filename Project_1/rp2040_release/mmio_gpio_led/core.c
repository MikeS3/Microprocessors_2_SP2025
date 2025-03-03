#include <ioregs.h>
#include <bitmanip.h>
#include <resets.h>

int main(void) {
	/* we first must take out IO_BANK0 out of reset mode */
	RESETS.reset &= ~(1u << RESETS_reset_io_bank0);	/* deassert reset bit */
	/* wait until the reset is done */
	loop_until_bit_is_set(RESETS.reset_done, RESETS_reset_done_io_bank0);

	/* set GPIO25 (LED_PIN) to use the SIO function */
	IO_BANK0.io[LED_PIN].ctrl = 5;			/* SIO driver for IO[LED_PIN] */

	/* and now we can set the pin to output */
	SIO.gpio_oe_set = (1u << LED_PIN);		/* set the pin as output */
	SIO.gpio_out_set = (1u << LED_PIN);		/* and set it high */
	return 0;
}
