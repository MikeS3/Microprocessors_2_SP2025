#ifndef SYSTICK_H__
#define SYSTICK_H__

extern struct {
    volatile unsigned csr;
    volatile unsigned rvr;
    volatile unsigned cvr;
    const unsigned calib;
} SYSTICK;

#define TICKINT_OFFSET		(1 << 1)

#endif
