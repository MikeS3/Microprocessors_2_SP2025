#include "rtc.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt.h"
#include "resets.h"
#include "bitmanip.h"
#include "clocks.h"
// Define external oscillator frequency in Hz
#define XOSC_FREQ_HZ 12000000

// Flag to track RTC interrupts
volatile bool rtc_interrupt_occurred = false;

/** rtc_init: Initializes the RTC peripheral */
void rtc_init(void) {
    // Bring RTC out of reset
    RESETS.reset &= ~(1u << RESETS_rtc);
    loop_until_bit_is_set(RESETS.reset_done, RESETS_rtc);
    

    //CLOCKS.clk_rtc_ctrl 
    // Set divider minus 1 xosc 12Mhz/256 = 46875hhz  
    //RTC.clkdiv_m1 = (XOSC_FREQ_HZ / 256) - 1;
    CLOCKS.clk_rtc_ctrl = (1u << CLOCKS_enable) | CLOCKS_RTC_xosc_clksrc; //xosc
    CLOCKS.clk_rtc_div = (256 << 8) | 0x00;  // INT = 256, FRAC = 0

    RTC.clkdiv_m1 = 46874;
    // Enable RTC
    RTC.ctrl = RTC_CTRL_LOAD | RTC_CTRL_ENABLE;

    // Clear any pending interrupts
    RTC.intf = RTC_INTR_BIT;
    
     // Debug message
     //uart0_puts("RTC initialized successfully\r\n");
     /* provided that the RTC starts at all 0's */
    RTC.irq_setup_1 = (1u << 8) | (1u << 29); /* match minute = 1 */
    RTC.irq_setup_0 = (1u << 28);  /* enable global match */
    RTC.inte = 1; /* enable the interrupt */
    NVIC_ISER = 1u << NVIC_BIT(RTC_vect); /* and enable it on the NVIC */
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
    //RTC.irq_setup_0 &= ~(1u << 28); // RTC_MATCH_ENA
    
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
    

    // Enable global match
    //RTC.irq_setup_0 |= (1u << 28); // RTC_MATCH_ENA
}

void rtc_clear_alarm(void) {
    RTC.irq_setup_0 &= ~(1u << 28); // Disable match
    RTC.inte &= ~RTC_INTR_BIT;     // Disable interrupt
    RTC.intf = RTC_INTR_BIT;       // Clear any pending
}

void rtc_schedule_next_alarm(void) {
    unsigned day, month, year, hours, minutes, seconds;

    // Get current time
    rtc_get_datetime(&day, &month, &year, &hours, &minutes, &seconds);



#define TEST_ALARM_10S 0  // Set to 0 for 1-minute alarm, 1 for 10-second test alarm

#if TEST_ALARM_10S 
    // test mode 10 seconds
    seconds += 10;
    if (seconds >= 60) {
        seconds -= 60;
        minutes += 1;
        if (minutes >= 60) {
            minutes = 0;
            hours += 1;
            if (hours >= 24)
                hours = 0;
        }
    }
#else
    // every 1 minute
    minutes += 1;
    if (minutes >= 60) {
        minutes -= 60;
        hours += 1;
        if (hours >= 24)
            hours = 0;
    }
#endif

    // Set the new alarm
    rtc_set_alarm(day, month, year, hours, minutes, seconds);
}


// Define a volatile counter variable to track alarms
volatile unsigned int rtc_alarm_count = 0; 

// Interrupt Service Routine for RTC
ISR(RTC_vect) {
    // 1) Clear the match interrupt flag
    //RTC.intf = RTC_INTR_BIT;

    // 2) Increment the counter to track how many alarms occurred
    rtc_alarm_count++;

    // 3) Schedule the next alarm for the next minute
    rtc_schedule_next_alarm();
}
