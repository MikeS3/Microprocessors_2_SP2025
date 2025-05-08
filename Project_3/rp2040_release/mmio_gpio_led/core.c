#include <bitmanip.h>
#include <clocks.h>
#include <resets.h>
#include "uart0.h"
#include "rtc.h"
#include "pio.h"
#include <uart-baud.h>
#include <uart.h>
#include <systick.h>
#include "llinit.h"
#include "adc.h"
#include <bitmanip.h>
#include <ioregs.h>
#include <pio.h>
#include "i2c.h"
#include "mpu6050.h"


//Using GCC macro to take the string of time at compiling, and convert it to numbers
#define HOURS       ((__TIME__[0] - '0') * 10 + (__TIME__[1] - '0'))
#define MINUTES(x) ((x[3] - '0') * 10 + (x[4] - '0'))
#define SECONDS     ((__TIME__[6] - '0') * 10 + (__TIME__[7] - '0'))

unsigned num[6] = {0};
int main(void) {
    low_level_init();
    //INITIALIZE UART rtc and SPI
    //uart0_init();
    //spi0_init();
    //adc_init();
    i2c_init();
    mpu6050_init();
    uint8_t acceleration[6];
    while(1)
    {
        mpu6050_get_acc(acceleration);
        num[0] = acceleration[0];
        num[1] = acceleration[1];
        num[2] = acceleration[2];
        num[3] = acceleration[3];
        num[4] = acceleration[4];
        num[5] = acceleration[5];
        num[6] = acceleration[6];

    }


	SIO. = (1u << GPIO_TRIGGER);
    return 0;
}
