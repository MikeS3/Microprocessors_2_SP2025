#ifndef SPI0_H__
#define SPI0_H__

extern struct {
/* 000 */	volatile unsigned sspcr0;
/* 004 */	volatile unsigned sspcr1;
/* 008 */	volatile unsigned sspdr;
/* 00c */	volatile unsigned sspsr;
/* 010 */	volatile unsigned sspcpsr;
/* 014 */	volatile unsigned sspimsc;
/* 018 */	volatile unsigned sspris;
/* 01c */	volatile unsigned sspmis;
/* 020 */	volatile unsigned sspicr;
/* 024 */	volatile unsigned sspdmacr;
} SPI0, SPI1;

#define SPI_CR1_MS          (2)
#define SPI_CR0_SCR_OFFSET  (8)
#define SPI_CR0_SCR_MASK    ((0xFF)<<8)
/*
#define UART_WLEN_7		(0x2)
#define UART_WLEN_6		(0x1)
#define UART_WLEN_5		(0x0)
#define UART_LCR_H_WLEN_OFFSET	(5)
#define UART_LCR_H_WLEN_MASK		((0x3) << (5))
#define UART_LCR_H_FEN	(4)

#define UART_FR_BUSY	(3)
#define UART_FR_TXFF	(5)


#define UART_CR_UARTEN		(0)
#define UART_CR_TXE			(8)
#define UART_CR_RXE			(9)

#define UART_IMSC_TXIM		(5)
#define UART_IMSC_RXIM		(4)
*/
#endif