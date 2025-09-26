#include "eeprom_service.h"
#include "../drivers/spi/spi_dma.h"
#include <stdio.h>

bool EEPROM_Write(uint16_t addr, const uint8_t *data, uint16_t len){
    // SPI DMA Write (예시)
    (void)addr; // 실제 EEPROM 주소 처리 필요
    (void)spi_write_dma(data, len);
    printf("EEPROM Write @0x%04X, len=%d\n", addr, len);
    return true;
}

bool EEPROM_Read(uint16_t addr, uint8_t *data, uint16_t len){
    // SPI DMA Read (예시)
    (void)addr;
    (void)spi_read_dma(data, len);
    printf("EEPROM Read @0x%04X, len=%d\n", addr, len);
    return true;
}
