#ifndef I2C_DMA_H
#define I2C_DMA_H
#include <stdint.h>
#include <stdbool.h>

typedef enum { I2C_IDLE, I2C_BUSY } i2c_state_t;

void i2c_init_dma(void);
bool i2c_read_dma(uint8_t addr7, uint8_t reg, uint8_t *buf, uint16_t len);
bool i2c_write_dma(uint8_t addr7, uint8_t reg, const uint8_t *buf, uint16_t len);
i2c_state_t i2c_get_state(void);

// ▷ DMA 완료/에러 ISR에서 호출
void i2c_dma_tx_cplt_isr(void);
void i2c_dma_rx_cplt_isr(void);
void i2c_dma_err_isr(void);

#endif
