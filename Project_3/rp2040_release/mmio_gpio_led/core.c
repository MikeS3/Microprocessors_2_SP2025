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
#include "pid.h"
#include "i2c.h"
#include "mpu6050.h"

//PID Adapted from https://github.com/pms67/PID/tree/master

/* Controller parameters */
#define PID_KP  2.0f
#define PID_KI  0.5f
#define PID_KD  0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f

#define SAMPLE_TIME_S 0.01f

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

    //mpu6050_get_acc(acceleration);

    PIDController pid = { PID_KP, PID_KI, PID_KD,
        PID_TAU,
        PID_LIM_MIN, PID_LIM_MAX,
        PID_LIM_MIN_INT, PID_LIM_MAX_INT,
        SAMPLE_TIME_S };

    PIDController_Init(&pid);

    fixedpt setpoint = 0; // vertical acceleration must be 0
    while(true)
    {

    mpu6050_get_acc(acceleration); // get acceleration data
    //break acceleration data up to find vertical acceleration using trig
    PIDController_Update(&pid, setpoint, acceleration); // pass acceleration array into pidcontroller (type hasnt been fixed)
    //PID controller also doesnt, break apart accelration array into x, y, and z components yet

    Update_motor_controller(&pid); //update the motor controller based on PID controller
    
    }

        #if 0
    while(1){
    
        PIDController_Update(&pid, setpoint, measurement);

    }
        #endif

    
    /*
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

    }*/

    return 0;
}
