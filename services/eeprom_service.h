#ifndef EEPROM_SERVICE_H
#define EEPROM_SERVICE_H
#include <stdint.h>
#include <stdbool.h>

bool EEPROM_Write(uint16_t addr, const uint8_t *data, uint16_t len);
bool EEPROM_Read(uint16_t addr, uint8_t *data, uint16_t len);

#endif
