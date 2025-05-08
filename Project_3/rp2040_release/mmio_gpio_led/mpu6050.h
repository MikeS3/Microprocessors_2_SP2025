#ifndef MPU6050_H__
#define MPU6050_H__


void mpu6050_init(void);
void mpu6050_get_acc(uint8_t*);

#define MPU6050_I2C_ADDRESS 0x34


#endif  /* MPU6050_H__ */