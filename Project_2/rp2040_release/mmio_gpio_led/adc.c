#include "adc.h"
#include "clocks.h"

void adc_init(void) {
    // Enable ADC
    ADC.cs = ADC_CS_EN;

    // Clear errors and FIFO
    ADC.fcs = ADC_FCS_EN | ADC_FCS_SHIFT | ADC_FCS_OVER | ADC_FCS_UNDER;
    ADC.cs  |= ADC_CS_ERR_STICKY;

    CLOCKS.clk_adc_ctrl = (1u << CLOCKS_enable) | (CLOCKS_ADC_clk_clksrc_pll_usb);

    CLOCKS.clk_adc_div = ( 256 << 8) | 0x00;
    //47999
    while (CLOCKS.clk_adc_selected != 0x1);
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

