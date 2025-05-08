#include <stdint.h>
#include "mpu6050.h"
#include <i2c.h>

void mpu6050_init(void)
{
    i2c_write(0x6B, (const uint8_t[]){0}, 1); //initialize MPU6050 by writing 0 to 0x6B register. 0 may need to address
    delay(100000);
    //write to ACCEL CONFIG REGISTER (0x1C)
    i2c_write(0x1C, (const uint8_t[]){1}, 1); // 1 data may need to be address
    //write to FIFO enable??
    delay(100000);
    //delay for MPU6050 to wake up from sleep mode
}

void mpu6050_get_acc(uint8_t* component_buffer){ // change to short to put upper and lower parts of accel together

    //send 6 bytes, starting at the XOUT UPPER 0x3B - 0x40 ZOUT_LOWER
    i2c_write_read(0x3B, component_buffer, 6);
}

