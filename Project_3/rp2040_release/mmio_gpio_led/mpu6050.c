#include "mpu6050.h"
#include <i2c.h>

void mpu6050_init(void)
{
    //i2c_write(MPU6050_I2C_ADDRESS, data); initialize MPU6050 by writing 0 to 0x6B register.
    //write to ACCEL CONFIG REGISTER (0x1C)
    //write to FIFO enable??
    //delay for MPU6050 to wake up from sleep mode
}


