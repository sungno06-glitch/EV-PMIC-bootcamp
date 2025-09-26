#include "spi_dma.h"

static volatile spi_state_t s_state = SPI_IDLE;
static uint8_t *s_rx; static const uint8_t *s_tx; static uint16_t s_len;

void spi_init_dma(void){
    s_state = SPI_IDLE;
    // TODO: SPI + DMA init, NVIC enable
}

bool spi_write_dma(const uint8_t *tx, uint16_t len){
    if (s_state != SPI_IDLE) return false;
    s_state = SPI_BUSY; s_tx = tx; s_len = len;
    // TODO: HW: SPI TX DMA start
    return true;
}

bool spi_read_dma(uint8_t *rx, uint16_t len){
    if (s_state != SPI_IDLE) return false;
    s_state = SPI_BUSY; s_rx = rx; s_len = len;
    // TODO: HW: SPI RX DMA start (full-duplex dummy TX)
    return true;
}

void spi_dma_tx_cplt_isr(void){ s_state = SPI_IDLE; }
void spi_dma_rx_cplt_isr(void){ s_state = SPI_IDLE; }
void spi_dma_err_isr(void){    s_state = SPI_IDLE; }
spi_state_t spi_get_state(void){ return s_state; }
