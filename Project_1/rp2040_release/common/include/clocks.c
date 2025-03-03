#include "clocks.h"

void xosc_init(void) {
	xosc_hw->ctrl =  XOSC_enable | XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ;

	xosc_hw->startup = 0xC4;

    while (!(xosc_hw->status & (1u << XOSC_stable))) {
        tight_loop_contents();
	}

 	CLOCKS.clk_peri_ctrl = CLOCKS_PERI_xosc_clksrc | (1u << CLOCKS_enable);

}

int main() {
    init_xosc();  

}
