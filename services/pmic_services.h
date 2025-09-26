#ifndef PMIC_SERVICE_H
#define PMIC_SERVICE_H
#include <stdint.h>

void pmic_check_faults(void);
void pmic_set_voltage(uint16_t mv);

#endif
