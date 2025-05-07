#ifndef UART0_H__
#define UART0_H__

#include <stddef.h>
#include <sys/types.h>
#include <stdint.h>
#define BAUD 115200
#define F_PERIPH 12000000ULL

void uart0_init(void);
ssize_t uart0_write(const char* msg, size_t l);
void uart0_putc(char c);
void uart0_puts(const char *s);
char uart0_getc(void);
int uart0_rx_ready(void);

#define UART0_TX_GPIO	(0)
#define UART0_RX_GPIO	(1)

#endif	/* UART0_H__ */
