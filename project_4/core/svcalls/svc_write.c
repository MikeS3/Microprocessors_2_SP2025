#include <stddef.h>
#include <syscall_list.h>
#include "uart.h"
int svc_write(const void* data, size_t len) {
	const char* d = (const char*)data;
	(void)len;
	(void)d;

//#	warning "implement this function"
    if (d == NULL || len == 0) {
		return -1;   //safty checck for null or empty
	}

    for (size_t i = 0; i < len; ++i) {
        // Wait until TX is not full
        while (UART0.uartfr & (1u << UART_FR_TXFF))
            ;

        // Write next character
        UART0.uartdr = (unsigned)d[i];
    }

    return (int)len;
}

