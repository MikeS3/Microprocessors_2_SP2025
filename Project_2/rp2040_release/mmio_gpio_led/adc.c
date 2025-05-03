#include "adc.h"

#define ADC_BASE 0x4004C000
#define REG32(addr) (*(volatile unsigned *)(addr))

// Bind the ADC struct to the hardware register base
volatile struct {
    volatile unsigned cs;
    volatile unsigned result;
    volatile unsigned fcs;
    volatile unsigned fifo;
    volatile unsigned div;
    volatile unsigned intr;
    volatile unsigned inte;
    volatile unsigned intf;
    volatile unsigned ints;
} * const ADC = (void *)ADC_BASE;

void adc_init(void) {
    // Enable the ADC
    ADC.cs = ADC_CS_EN;

    // Enable FIFO with shifting enabled so results are 8-bit if desired
    ADC.fcs = ADC_FCS_EN | ADC_FCS_SHIFT;

    // Optional: Set clock divider (e.g., divide by 96 = 0x600)
    ADC.div = (96 << ADC_DIV_INT_LSB);

    // Clear errors and FIFO
    ADC.fcs |= ADC_FCS_OVER | ADC_FCS_UNDER;
    ADC.cs  |= ADC_CS_ERR_STICKY;
}

unsigned adc_read(unsigned channel) {
    // Select the ADC input channel
    ADC.cs = (ADC.cs & ~ADC_CS_AINSEL_MASK) | ((channel << ADC_CS_AINSEL_LSB) & ADC_CS_AINSEL_MASK);

    // Start a single conversion
    ADC.cs |= ADC_CS_START_ONCE;

    // Wait until the result is ready
    while (!(ADC.cs & ADC_CS_READY));

    // Return the 12-bit result
    return ADC.result & ADC_RESULT_MASK;
}

void adc_enable_temp_sensor(unsigned enable) {
    if (enable)
        ADC.cs |= ADC_CS_TS_EN;
    else
        ADC.cs &= ~ADC_CS_TS_EN;
}
