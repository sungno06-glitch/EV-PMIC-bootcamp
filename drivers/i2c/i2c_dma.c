#include "i2c_dma.h"

static volatile i2c_state_t s_state = I2C_IDLE;
static uint8_t *s_rx;
static const uint8_t *s_tx;
static uint16_t s_len;
static uint8_t s_addr, s_reg;

void i2c_init_dma(void){
    s_state = I2C_IDLE;
    // TODO: I2C + DMA init, NVIC enable
}

bool i2c_read_dma(uint8_t addr7, uint8_t reg, uint8_t *buf, uint16_t len){
    if (s_state != I2C_IDLE) return false;
    s_state = I2C_BUSY; s_rx = buf; s_len = len; s_addr = addr7; s_reg = reg;
    // TODO: HW: I2C Mem Read DMA (addr7<<1 | R, reg, len)
    return true;
}

bool i2c_write_dma(uint8_t addr7, uint8_t reg, const uint8_t *buf, uint16_t len){
    if (s_state != I2C_IDLE) return false;
    s_state = I2C_BUSY; s_tx = buf; s_len = len; s_addr = addr7; s_reg = reg;
    // TODO: HW: I2C Mem Write DMA (addr7<<1 | W, reg, len)
    return true;
}

// ▷ 아래 3개는 실제 DMA 콜백(인터럽트)에서 호출
void i2c_dma_tx_cplt_isr(void){ s_state = I2C_IDLE; }
void i2c_dma_rx_cplt_isr(void){ s_state = I2C_IDLE; }
void i2c_dma_err_isr(void){   s_state = I2C_IDLE; /* 에러 플래그 추가 가능 */ }

i2c_state_t i2c_get_state(void){ return s_state; }
