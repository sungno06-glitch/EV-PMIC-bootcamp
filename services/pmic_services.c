#include "../drivers/i2c/i2c_dma.h"
#include "../include/app_config.h"
#include "dtc_manager.h"
#include <stdio.h>

// PMIC Register (예시 주소)
#define PMIC_REG_VOUT_SETTING  0x20
#define PMIC_REG_UV_FAULT      0x10
#define PMIC_REG_OC_FAULT      0x11

static uint8_t uv_status = 0;
static uint8_t oc_status = 0;

void pmic_check_faults(void){
    if (i2c_get_state()==I2C_IDLE){
        (void)i2c_read_dma(0x40, PMIC_REG_UV_FAULT, &uv_status, 1);
        (void)i2c_read_dma(0x40, PMIC_REG_OC_FAULT, &oc_status, 1);
    }

    if (uv_status & 0x01){
        printf("UV Fault Detected!\n");
        DTC_Save(0xC101);
    }
    if (oc_status & 0x01){
        printf("OC Fault Detected!\n");
        DTC_Save(0xC102);
    }
}

/// PMIC 전압 레벨 변경 (mV 단위)
void pmic_set_voltage(uint16_t mv){
    uint8_t regval = 0;

    // 예시 변환식: 10mV step (데이터시트 참고 필요)
    regval = (uint8_t)(mv / 10);

    if (i2c_get_state()==I2C_IDLE){
        (void)i2c_write_dma(0x40, PMIC_REG_VOUT_SETTING, &regval, 1);
        printf("Set PMIC VOUT to %u mV (reg=0x%02X)\n", mv, regval);
    }
}
