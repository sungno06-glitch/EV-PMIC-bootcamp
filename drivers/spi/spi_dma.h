#ifndef SPI_DMA_H
#define SPI_DMA_H
#include <stdint.h>
#include <stdbool.h>

typedef enum { SPI_IDLE, SPI_BUSY } spi_state_t;

void spi_init_dma(void);
bool spi_write_dma(const uint8_t *tx, uint16_t len);
bool spi_read_dma(uint8_t *rx, uint16_t len);
spi_state_t spi_get_state(void);

// ▷ DMA 완료/에러 ISR에서 호출
void spi_dma_tx_cplt_isr(void);
void spi_dma_rx_cplt_isr(void);
void spi_dma_err_isr(void);

#endif
