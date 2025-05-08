#ifndef I2C_H__
#define I2C_H__

void i2c_init(void);
void i2c_write(uint8_t, uint8_t*, uint8_t );
void i2c_write_read(uint8_t, uint8_t*, uint8_t); // really a write read

extern struct {
/* 00 */	volatile unsigned con;
/* 04 */	volatile unsigned tar;
/* 08 */	volatile unsigned sar;
/* 0c */	unsigned __padding_0;
/* 10 */	volatile unsigned data_cmd;
/* 14 */	volatile unsigned ss_scl_hcnt;
/* 18 */	volatile unsigned ss_scl_lcnt;
/* 1c */	volatile unsigned fs_scl_hcnt;
/* 20 */	volatile unsigned fs_scl_lcnt;
/* 24,28 */	unsigned __padding_1[2];
/* 2c */	volatile unsigned intr_stat;
/* 30 */	volatile unsigned intr_mask;
/* 34 */	volatile unsigned raw_intr_stat;
/* 38 */	volatile unsigned rx_tl;
/* 3c */	volatile unsigned tx_tl;
/* 40 */	volatile unsigned ctrl_intr;
/* 44 */	struct {
/* 44 */		volatile unsigned rx_under;
/* 48 */		volatile unsigned rx_over;
/* 4c */		volatile unsigned tx_over;
/* 50 */		volatile unsigned rd_req;
/* 54 */		volatile unsigned tx_abrt;
/* 58 */		volatile unsigned rx_done;
/* 5c */		volatile unsigned activity;
/* 60 */		volatile unsigned stop_det;
/* 64 */		volatile unsigned start_det;
/* 68 */		volatile unsigned gen_call;
/*    */	} clr;
/* 6c */	volatile unsigned enable;
/* 70 */	volatile unsigned status;
/* 74 */	volatile unsigned txflr;
/* 78 */	volatile unsigned rxflr;
/* 7c */	volatile unsigned sda_hold;
/* 80 */	volatile unsigned tx_abrt_source;
/* 84 */	volatile unsigned slv_data_nack_only;
/* 88 */	struct {
/* 88 */		volatile unsigned cr;
/* 8c */		volatile unsigned tdlr;
/* 90 */		volatile unsigned rdlr;
/*    */	} dma;
/* 94 */	volatile unsigned ic_sda_setup;
/* 98 */	volatile unsigned ic_ack_general_call;
/* 9c */	volatile unsigned ic_enable_status;
/* a0 */	volatile unsigned ic_fs_spklen;
/* a4 */	volatile unsigned ic_clr_restart_det;
/* meh */
// /* f4 */	volatile unsigned ic_comp_param_1;
// /* f8 */	volatile unsigned ic_comp_version;
// /* fc */	volatile unsigned ic_comp_type;
} I2C0, I2C1;

#define IC_CON_SLAVE_DISABLE    (1 << 6)
#define IC_CON_RESTART_EN       (1 << 5)
#define IC_CON_ADDRESS_7BITS     (1 << 3) // set to 0
#define IC_CON_SPEED            (1 << 1) //set to standard speed 100kbits
#define IC_CON_MASTER_MODE      (1)

#define IC_TAR_OFFSET           (0)

#define IC_ENABLE               (0) // 0 to disable 1 to enable

#define IC_STATUS_MST_ACTIVITY  (1 << 5)
#define IC_STATUS_RFNE          (1 << 3) // Recieve FIFO NOT EMPTY
#define IC_STATUS_TFE           (1 << 2) //Transmit FIFO Empty

#define IC_TXFLR_OFFSET         (0) //5 bytes contains the number of valid entries in transmit FIFO

#define IC_RXFLR_OFFSET         (0) //5 bytes contains the number of valid entries in recieve FIFO

#define IC_DATA_CMD_MASK        (0xFF)
#define IC_DATA_CMD_CMD         (1 << 8) //1 for master read 0 for master write    
#define IC_DATA_CMD_STOP        (1 << 9) //STOP bit
#define IC_DATA_CMD_DAT         (0)

#define I2C_SDA_GPIO            (8)
#define I2C_SCL_GPIO            (9)


#endif	/* I2C_H__ */
