#ifndef DTC_MANAGER_H
#define DTC_MANAGER_H
#include <stdint.h>

void DTC_Save(uint16_t code);
uint8_t DTC_ReadAll(uint16_t *out, uint8_t max);
void DTC_ClearAll(void);

#endif
