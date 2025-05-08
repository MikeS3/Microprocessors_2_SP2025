#ifndef MPU6050_H__
#define MPU6050_H__


void mpu6050_init(void);
void mpu6050_get_acc(uint8_t*);

#define MPU6050_I2C_ADDRESS 0x68

/* dirty software delay loop */
static inline void delay(unsigned n) {

	asm volatile (

		"1:	sub %[r0], #1"	"\n"

		"	bne 1b"

		: [r0]"+r"(n)

		:

		: "memory"

	);

}

#endif  /* MPU6050_H__ */