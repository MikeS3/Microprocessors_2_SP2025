#ifndef UART0_H__
#define UART0_H__

#include <stddef.h>
#include <sys/types.h>
#define BAUD 115200
#define F_PERIPH 12000000ULL

void uart0_init(void);
ssize_t uart0_write(const char* msg, size_t l);

#define UART0_TX_GPIO	(0)
#define UART0_RX_GPIO	(1)

#endif	/* UART0_H__ */
