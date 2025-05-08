#ifndef RTC_H__
#define RTC_H__

#include "resets.h"
#include <stdbool.h>

#define RTC_BASE 0x4005C000

// Control register bits
#define RTC_CTRL_ENABLE          (1u << 0)
#define RTC_CTRL_ACTIVE          (1u << 1)
#define RTC_CTRL_LOAD            (1u << 4)
#define RTC_CTRL_FORCE_NOTLEAP   (1u << 8)

// IRQ vector number
#define RTC_INTR_BIT             (1u << 0)
#define RTC_IRQ_NUM           41
#define RTC_IRQ_vect          RTC_IRQ_NUM

// RTC peripheral struct
extern struct {
    volatile unsigned clkdiv_m1;       // 0x00
    volatile unsigned setup_0;         // 0x04
    volatile unsigned setup_1;         // 0x08
    volatile unsigned ctrl;            // 0x0C
    volatile unsigned irq_setup_0;     // 0x10
    volatile unsigned irq_setup_1;     // 0x14
    volatile unsigned rtc_1;           // 0x18
    volatile unsigned rtc_0;           // 0x1C
    volatile unsigned intr;            // 0x20
    volatile unsigned inte;            // 0x24
    volatile unsigned intf;            // 0x28
    volatile unsigned ints;            // 0x2C
} RTC;
// Flag to track RTC interrupts
extern volatile bool rtc_interrupt_occurred;

// Function prototypes
void rtc_init(void);
void rtc_set_datetime(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds);
void rtc_get_datetime(unsigned* day, unsigned* month, unsigned* year, unsigned* hours, unsigned* minutes, unsigned* seconds);
void rtc_set_alarm(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds);
void rtc_clear_alarm(void);
void rtc_schedule_next_alarm(void);
#endif // RTC_H__