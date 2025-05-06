#include "rtc.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt.h"
#include "resets.h"

// Define this macro if it's not defined elsewhere
#ifndef loop_until_bit_is_set
#define loop_until_bit_is_set(sfr, bit) do { } while (!(sfr & (1u << bit)))
#endif

/** rtc_init: Initializes the RTC peripheral */
void rtc_init(void) {
    // Bring RTC out of reset
    RESETS.reset &= ~(1u << RESETS_rtc);
    loop_until_bit_is_set(RESETS.reset_done, RESETS_rtc);
    
    // Set divider minus 1  
    RTC.clkdiv_m1 = 0x7FFF;
    
    // Enable RTC
    RTC.ctrl = RTC_CTRL_LOAD | RTC_CTRL_ENABLE;
}

void rtc_set_datetime(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds) {
    RTC.rtc_0 = (seconds << 0) | (minutes << 8) | (hours << 16);
    RTC.rtc_1 = (day << 0) | (month << 8) | (year << 16);
}

void rtc_get_datetime(unsigned* day, unsigned* month, unsigned* year, unsigned* hours, unsigned* minutes, unsigned* seconds) {
    unsigned t0 = RTC.rtc_0;
    unsigned t1 = RTC.rtc_1;
    *seconds = (t0 >> 0) & 0xFF;
    *minutes = (t0 >> 8) & 0xFF;
    *hours   = (t0 >> 16) & 0xFF;
    *day     = (t1 >> 0) & 0xFF;
    *month   = (t1 >> 8) & 0xFF;
    *year    = (t1 >> 16) & 0xFFFF;
}

void rtc_set_alarm(unsigned day, unsigned month, unsigned year, unsigned hour, unsigned min, unsigned sec) {
    // Disable match before setting
    RTC.irq_setup_0 &= ~(1u << 28); // RTC_MATCH_ENA
    
    // Setup match fields
    RTC.irq_setup_0 = ((1u << 26) | // RTC_YEAR_ENA
                       (1u << 25) | // RTC_MONTH_ENA
                       (1u << 24) | // RTC_DAY_ENA
                       ((year & 0x0FFF) << 12) |
                       ((month & 0x0F) << 8) |
                       (day & 0x1F));
    
    RTC.irq_setup_1 = ((1u << 30) | // RTC_HOUR_ENA
                       (1u << 29) | // RTC_MIN_ENA
                       (1u << 28) | // RTC_SEC_ENA
                       ((hour & 0x1F) << 16) |
                       ((min & 0x3F) << 8) |
                       (sec & 0x3F));
    
    // Enable alarm interrupt
    RTC.inte |= (1u << 0); // RTC_INTE_BIT
    
    // Enable global match
    RTC.irq_setup_0 |= (1u << 28); // RTC_MATCH_ENA
}

void rtc_clear_alarm(void) {
    // Disable matching and alarm interrupt
    RTC.irq_setup_0 &= ~(1u << 28); // RTC_MATCH_ENA
    RTC.inte &= ~(1u << 0); // RTC_INTE_BIT
    RTC.intf &= ~(1u << 0); // RTC_INTE_BIT
}

/* RTC Interrupt Service Routine */
ISR(RTC_IRQ_vect) {
    if (RTC.irq_setup_0 & (1u << 29)) { // RTC_MATCH_ACTIVE
        // Clear interrupt
        RTC.intf = (1u << 0); // RTC_INTE_BIT
        // Do something, like toggle LED or signal event
    }
}