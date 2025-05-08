#include <stdint.h>
#include <bitmanip.h>
#include <ioregs.h>
#include "i2c.h"
#include "resets.h"
#include "mpu6050.h"

void i2c_init(void){
	//pull i2c0 out of reset
	RESETS.reset &= ~(1u << RESETS_i2c0);
	loop_until_bit_is_set(RESETS.reset_done, RESETS_i2c0);

	//disable i2c
	I2C0.enable = 0;

	IO_BANK0.io[I2C_SDA_GPIO].ctrl = 3;
	IO_BANK0.io[I2C_SCL_GPIO].ctrl = 3;

	//enable  master
	//disable slave 
	I2C0.con = (IC_CON_SLAVE_DISABLE |IC_CON_RESTART_EN
				| IC_CON_SPEED | IC_CON_MASTER_MODE & IC_CON_ADDRESS_7BITS
	);

	I2C0.tar = MPU6050_I2C_ADDRESS; // set slave address to MPU6050 address

	//loop_until_bit_is_set(I2C0.con, //I2C0.con)
	I2C0.enable = 1;
	//enable  fifo
	return;
}

//TODO need to change data type for send/read buffer Add error checking
void i2c_write(uint8_t register_address, uint8_t* send_buffer, uint8_t bytes_to_send){

	//send each byte
	I2C0.data_cmd = register_address & ~(IC_DATA_CMD_CMD);//set data command to write (0) on first byte along with first register
	//Do I need an 11 byte Mask to and with the data I am writing
	//~(I2C_IC_DATA_CMD_CMD) how to set to 0 and combine with register address
	
	//if(bytes)
	for(int i=0; i < bytes_to_send- 1; i++){
		//continue transmitting bytes
		I2C0.data_cmd = send_buffer[i];
	}
	I2C0.data_cmd = IC_DATA_CMD_STOP | send_buffer[bytes_to_send - 1]; // on the last byte, raise the stop flag
	//if txfifo not
	//while(!(I2C0.status | IC_STATUS_TFE));
		//loop until TX FIFO empty
	//send STOP

} 
void i2c_write_read(uint8_t register_address, uint8_t* read_buffer, uint8_t bytes_to_read){ // really a write read

	I2C0.data_cmd = register_address & ~(IC_DATA_CMD_CMD); // first write register address and write bit

	//Send restart condition

	while (!(I2C0.status & IC_STATUS_TFE)); // wait for Transmit FIFO to empty

		//read 6 times
		/*
	for(int i=0; i < bytes_to_read- 1; i++){ //  send read for every byte we need

		I2C0.data_cmd = IC_DATA_CMD_CMD;
	}
	I2C0.data_cmd = IC_DATA_CMD_STOP | IC_DATA_CMD_CMD; // send read for last byte, and stop bit
*/
	I2C0.data_cmd = IC_DATA_CMD_CMD; // send read

	for(int i=0; i < bytes_to_read; i++){

	//while(!(I2C0.status | IC_STATUS_RFNE)); // while Receive fifo empty

	read_buffer[i] = (uint8_t)(I2C0.data_cmd & IC_DATA_CMD_MASK);

	}
	I2C0.data_cmd = IC_DATA_CMD_CMD | IC_DATA_CMD_STOP; //send stop after read/

}


#if 0
#define I2C_READ_BIT_SHIFT (0)

#define TM1637_CMD1		(0x40) // 0x40 data command
#define TM1637_CMD2		(0xC0) // 0xC0 address command
#define TM1637_CMD3		(0x80) // 0x80 display control command

#define TM1637_CMD3_UNKOWN	BIT(4)
#define TM1637_CMD3_DSP_ON	BIT(3) // 0x08 display on

static inline void fix_i2c_SCL(void) {
	set_pinfunc(5, GPIO_FUNC_SIO); /* SCL, PICO PIN 7 */
	SIO_BASE[9] |= 1 << 5; // OE_SET
	delay(10000);
	set_pinfunc(5, GPIO_FUNC_I2C); /* SCL, PICO PIN 7 */
}

static inline uint8_t reverse8(uint8_t b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;

	return b;
}

static void set_command(uint8_t cmd, bool send) {
	cmd = reverse8(cmd);

	i2c_init(cmd & NBIT(I2C_READ_BIT_SHIFT));

	if (!send)
		return;

	if (!(cmd & BIT(I2C_READ_BIT_SHIFT))) {
		i2c_write_stop(0x00);
		return;
	}

	i2c_read_stop();
	delay(10000);

	fix_i2c_SCL();

	set_reset(RESETS_I2C0, 1);
	delay(10000);
	set_reset(RESETS_I2C0, 0);

	return;
}

void tm1637_init(void) {
	set_command(TM1637_CMD3 | TM1637_CMD3_DSP_ON | TM1637_CMD3_UNKOWN | 0x7, true);
	set_command(TM1637_CMD1, false);

	tm1637_write_segments((uint8_t[6]){0});

	/* shift so first byte is first digit */
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
	i2c_write_stop(0x00);
}

void tm1637_write_segments(uint8_t data[6]) {

	for (int i = 0; i < 5; i++)
		i2c_write(data[i]);

	i2c_write_stop(data[5]);
}
uint8_t i2c_read_stop(void) {
	loop_until_bit_is_set(I2C0_BASE[I2C_IC_STATUS], IC_STATUS_TFNF_SHIFT);
	I2C0_BASE[I2C_IC_DATA_CMD] = BIT(IC_DATA_CMD_STOP_SHIFT) | BIT(IC_DATA_CMD_CMD_SHIFT);

	while(!I2C0_BASE[I2C_IC_RXFLR]) {
		if(I2C0_BASE[I2C_IC_RAW_INTR_STAT] & IC_RAW_INTR_STAT_TX_ABRT_BITS)
			return 0;
	}

	return I2C0_BASE[I2C_IC_DATA_CMD];
}
	#endif