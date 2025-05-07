#include "rtc.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt.h"
#include "resets.h"
#include "bitmanip.h"
// Define external oscillator frequency in Hz
#define XOSC_FREQ_HZ 12000000

// Flag to track RTC interrupts
volatile bool rtc_interrupt_occurred = false;

/** rtc_init: Initializes the RTC peripheral */
void rtc_init(void) {
    // Bring RTC out of reset
    RESETS.reset &= ~(1u << RESETS_rtc);
    loop_until_bit_is_set(RESETS.reset_done, RESETS_rtc);
    
    // Set divider minus 1  
    RTC.clkdiv_m1 = XOSC_FREQ_HZ - 1;
    
    // Enable RTC
    RTC.ctrl = RTC_CTRL_LOAD | RTC_CTRL_ENABLE;

    // Clear any pending interrupts
    RTC.intf = RTC_INTR_BIT;
    
     // Debug message
     uart0_puts("RTC initialized successfully\r\n");
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
    
    // Enable interrupt
    RTC.inte |= RTC_INTR_BIT;
    
    // Enable global match
    RTC.irq_setup_0 |= (1u << 28); // RTC_MATCH_ENA
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
    
    // Add 10 seconds for the next alarm
    //seconds += 10;
    //5 minute alarms
    minutes += 5;
    if (minutes >= 60) {
        minutes -= 60;
        hours += 1;
    if (hours >= 24)
        hours -= 24;

    }
    // Set the alarm
    rtc_set_alarm(day, month, year, hours, minutes, seconds);
}

// Interrupt Service Routine for RTC
ISR(RTC_IRQ_vect) {
    // Confirm it's the RTC match interrupt
    if (RTC.intr & RTC_INTR_BIT) {
        // Clear interrupt flag
        RTC.intf = RTC_INTR_BIT;

        rtc_interrupt_occurred = true;

        uart0_puts("RTC Interrupt triggered!\r\n");

        rtc_schedule_next_alarm();
    }
}