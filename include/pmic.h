#ifndef PMIC_H
#define PMIC_H

#include <stdint.h>

/// I2C Slave Address (datasheet 기반, 가정값)
#define PMIC_I2C_SLAVE_ADDR   0x40

/// Fault Register Address (datasheet I2C Table 참고)
typedef enum {
    PMIC_REG_UV_FAULT   = 0x10,  // Under Voltage Fault Register
    PMIC_REG_OC_FAULT   = 0x11,  // Over Current Fault Register
    PMIC_REG_OT_FAULT   = 0x12   // Over Temperature Fault Register
} pmic_fault_reg_t;

/// 8-byte I2C Data Frame (Union + Bitfield)
typedef union {
    uint8_t raw[8];   ///< Raw 8-byte data access
    struct {
        uint8_t uv_fault  : 1;  ///< Under Voltage Fault
        uint8_t oc_fault  : 1;  ///< Over Current Fault
        uint8_t ot_fault  : 1;  ///< Over Temperature Fault
        uint8_t reserved  : 5;  ///< Reserved bits
    } bits;
} pmic_data_t;

/// Function prototypes
void PMIC_Init(void);
uint8_t PMIC_ReadFault(pmic_fault_reg_t reg, pmic_data_t* data);
void PMIC_ClearFault(pmic_fault_reg_t reg);

#endif // PMIC_H
