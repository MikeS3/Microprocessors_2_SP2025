#ifndef UART_H__
#define UART_H__

extern struct {
/* 000 */	volatile unsigned uartdr;
/* 004 */	volatile unsigned uartrsr;
/* 000 */	unsigned __padding_1[0x14/4]; /* padding of 0x14 */
/* 018 */	volatile unsigned uartfr;
/* 000 */	unsigned __padding_2[2];	/* padding of 8 */
/* 020 */	volatile unsigned uartilpr;
/* 024 */	volatile unsigned uartibrd;
/* 028 */	volatile unsigned uartfbrd;
/* 02c */	volatile unsigned uartlcr_h;
/* 030 */	volatile unsigned uartcr;
/* 034 */	volatile unsigned uartifls;
/* 038 */	volatile unsigned uartimsc;
/* 03c */	volatile unsigned uartris;
/* 040 */	volatile unsigned uartmis;
/* 044 */	volatile unsigned uarticr;
/* 048 */	volatile unsigned uartdmacr;
} UART0, UART1;

#endif
