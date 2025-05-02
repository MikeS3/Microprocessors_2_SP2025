#ifndef SPI0_H__
#define SPI0_H__

#define SPI_CLOCK_PRESCALER

void spi0_init(void);
void spi0_send(unsigned short message);

#endif