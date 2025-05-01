#ifndef RTC_H__
#define RTC_H__


extern struct {
    /* 0x00 */ volatile unsigned clkdiv_m1;
    /* 0x04 */ volatile unsigned setup_0;
    /* 0x08 */ volatile unsigned setup_1;
    /* 0x0C */ volatile unsigned ctrl;
    /* 0x10 */ volatile unsigned irq_setup_0;
    /* 0x14 */ volatile unsigned irq_setup_1;
    /* 0x18 */ volatile unsigned rtc_1;
    /* 0x1C */ volatile unsigned rtc_0;
} RTC;

// --- CTRL Register bits ---
#define RTC_CTRL_ENABLE     (1u << 0)
#define RTC_CTRL_LOAD       (1u << 4)

// --- Function prototype ---
void rtc_init(void);
void rtc_set_datetime(unsigned day, unsigned month, unsigned year, unsigned hours, unsigned minutes, unsigned seconds);
void rtc_get_datetime(unsigned* day, unsigned* month, unsigned* year, unsigned* hours, unsigned* minutes, unsigned* seconds);

#endif // RTC_H__
