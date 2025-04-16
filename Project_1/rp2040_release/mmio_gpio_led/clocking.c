#include <bitmanip.h>
#include <clocks.h>
#include <resets.h>

#include "clocking.h"


void clocking_init(void) {
	RESETS.reset &= ~(1u << RESETS_pll_sys);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_pll_sys);

	XOSC.ctrl = XOSC_enable | XOSC_freq_range_1_15MHz;
	loop_until_bit_is_set(XOSC.status, XOSC_stable);

	CLOCKS.clk_peri_ctrl =
				(1u << CLOCKS_enable)
			|	(CLOCKS_PERI_xosc_clksrc);
}
