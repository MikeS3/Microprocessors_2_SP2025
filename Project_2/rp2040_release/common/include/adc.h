#ifndef ADC_H__
#define ADC_H__
#define ADC_BASE 0x4004C000

// ADC Register Map
extern struct {
    /* 0x00 */ volatile unsigned cs;
    /* 0x04 */ volatile unsigned result;
    /* 0x08 */ volatile unsigned fcs;
    /* 0x0C */ volatile unsigned fifo;
    /* 0x10 */ volatile unsigned div;
    /* 0x14 */ volatile unsigned intr;
    /* 0x18 */ volatile unsigned inte;
    /* 0x1C */ volatile unsigned intf;
    /* 0x20 */ volatile unsigned ints;
} ADC;

// --- CS Register Bits ---
#define ADC_CS_EN              (1u << 0)
#define ADC_CS_TS_EN           (1u << 1)
#define ADC_CS_START_ONCE      (1u << 2)
#define ADC_CS_START_MANY      (1u << 3)
#define ADC_CS_READY           (1u << 8)
#define ADC_CS_ERR             (1u << 9)
#define ADC_CS_ERR_STICKY      (1u << 10)
#define ADC_CS_AINSEL_LSB      12
#define ADC_CS_AINSEL_MASK     (0x7u << ADC_CS_AINSEL_LSB)
#define ADC_CS_RROBIN_LSB      16
#define ADC_CS_RROBIN_MASK     (0x1Fu << ADC_CS_RROBIN_LSB)

// --- RESULT Register ---
#define ADC_RESULT_MASK        0x0FFFu  // 12-bit result

// --- FCS Register Bits ---
#define ADC_FCS_EN             (1u << 0)
#define ADC_FCS_SHIFT          (1u << 1)
#define ADC_FCS_ERR            (1u << 2)
#define ADC_FCS_DREQ_EN        (1u << 3)
#define ADC_FCS_EMPTY          (1u << 8)
#define ADC_FCS_FULL           (1u << 9)
#define ADC_FCS_UNDER          (1u << 10)
#define ADC_FCS_OVER           (1u << 11)
#define ADC_FCS_LEVEL_LSB      16
#define ADC_FCS_LEVEL_MASK     (0xFu << ADC_FCS_LEVEL_LSB)
#define ADC_FCS_THRESH_LSB     24
#define ADC_FCS_THRESH_MASK    (0xFu << ADC_FCS_THRESH_LSB)

// --- FIFO Register Bits ---
#define ADC_FIFO_ERR           (1u << 15)
#define ADC_FIFO_VAL_MASK      0x0FFFu

// --- DIV Register Bits ---
#define ADC_DIV_FRAC_MASK      0xFFu
#define ADC_DIV_INT_LSB        8
#define ADC_DIV_INT_MASK       (0xFFFFu << ADC_DIV_INT_LSB)

// --- Interrupt Registers (INTR, INTE, INTF, INTS) ---
#define ADC_IRQ_FIFO           (1u << 0)

// --- Function Prototypes ---
void adc_init(void);
unsigned adc_read(unsigned channel);
void adc_enable_temp_sensor(unsigned enable);

#endif // ADC_H__
