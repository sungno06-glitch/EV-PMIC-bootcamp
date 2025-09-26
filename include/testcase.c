#include "../include/testcase.h"
#include "../services/pmic_service.h"
#include "../services/dtc_manager.h"
#include "../services/uds_handler.h"
#include "../drivers/can/can_isr.h"
#include "../drivers/uart/uart_poll.h"
#include <stdio.h>

#if TESTCASE

// White-box Test 1: VOUT 레벨 변경
void run_whitebox_tc1(void){
    printf("[TC-W1] PMIC VOUT set to 3300 mV\n");
    pmic_set_voltage(3300);
    printf("[TC-W1] PMIC VOUT set to 5000 mV\n");
    pmic_set_voltage(5000);
}

// White-box Test 2: DTC 저장 및 삭제
void run_whitebox_tc2(void){
    printf("[TC-W2] Save DTC 0xC101\n");
    DTC_Save(0xC101);
    printf("[TC-W2] Save DTC 0xC102\n");
    DTC_Save(0xC102);

    uint16_t buf[4];
    uint8_t n = DTC_ReadAll(buf, 4);
    printf("[TC-W2] ReadAll DTC count=%d\n", n);

    DTC_ClearAll();
    n = DTC_ReadAll(buf, 4);
    printf("[TC-W2] After clear, DTC count=%d\n", n);
}

// Black-box Test 1: UDS ReadDTC (0x19)
void run_blackbox_tc1(void){
    can_msg_t rx;
    rx.id = 0x7DF;  // Tester → ECU
    rx.len = 1;
    rx.data[0] = 0x19;

    printf("[TC-B1] Sending UDS ReadDTC request\n");
    UDS_HandleMessage(&rx);
}

// Black-box Test 2: UDS ClearDTC (0x14)
void run_blackbox_tc2(void){
    can_msg_t rx;
    rx.id = 0x7DF;
    rx.len = 1;
    rx.data[0] = 0x14;

    printf("[TC-B2] Sending UDS ClearDTC request\n");
    UDS_HandleMessage(&rx);
}

void run_all_tests(void){
    run_whitebox_tc1();
    run_whitebox_tc2();
    run_blackbox_tc1();
    run_blackbox_tc2();
}

#endif // TESTCASE
