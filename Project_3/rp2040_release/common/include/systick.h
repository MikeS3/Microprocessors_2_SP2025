#ifndef SYSTICK_H__
#define SYSTICK_H__

extern struct {
    volatile unsigned csr;
    volatile unsigned rvr;
    volatile unsigned cvr;
    const unsigned calib;
} SYSTICK;

#define TICKINT_OFFSET		(0x1 << 1)
#define CLKSOURCE_OFFSET    (0x1 << 2)

#endif
