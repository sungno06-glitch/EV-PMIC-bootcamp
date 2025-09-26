#include "dtc_manager.h"
#include <stdio.h>

#define MAX_DTC 16
static uint16_t dtc_list[MAX_DTC];
static uint8_t dtc_count = 0;

void DTC_Save(uint16_t code){
    if (dtc_count < MAX_DTC){
        dtc_list[dtc_count++] = code;
        printf("DTC 0x%04X saved\n", code);
    }
}

uint8_t DTC_ReadAll(uint16_t *out, uint8_t max){
    uint8_t n = (dtc_count < max) ? dtc_count : max;
    for (int i=0; i<n; i++) out[i] = dtc_list[i];
    return n;
}

void DTC_ClearAll(void){
    dtc_count = 0;
    printf("All DTCs cleared\n");
}
