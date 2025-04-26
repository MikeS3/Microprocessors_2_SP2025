#include "rtc.h"
#include <bitmanip.h>
#include <interrupt.h>
#include <ioregs.h>
#include <resets.h>

/** rtc_init: Initializes the RTC peripheral */
void rtc_init(void) {
    // Bring RTC out of reset
    RESETS->reset &= ~(1u << RESETS_rtc);
    loop_until_bit_is_set(RESETS->reset_done, RESETS_rtc);

    // Set divider minus 1 
    RTC.clkdiv_m1 = 0x7FFF; 

    // Enable RTC
    RTC.ctrl = RTC_CTRL_LOAD | RTC_CTRL_ENABLE;
}

/* Optional RTC Interrupt Service Routine */
ISR(RTC_IRQ_vect) {
    (void)RTC; // suppress unused warning for now
}