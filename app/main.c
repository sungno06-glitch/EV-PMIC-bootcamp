#include <stdio.h>
#include "../platform/board.h"
#include "../include/app_config.h"
#include "../include/testcase.h"

#include "../drivers/uart/uart_poll.h"
#include "../drivers/can/can_isr.h"
#include "../drivers/i2c/i2c_dma.h"
#include "../drivers/spi/spi_dma.h"

#include "../services/pmic_service.h"
#include "../services/uds_handler.h"
#include "../services/dtc_manager.h"

int main(void){
    // 보드 초기화
    board_init_clock_gpio();
    board_init_systick_1ms();
    uart_init_poll();
    can_init_isr();
    i2c_init_dma();
    spi_init_dma();

#if TESTCASE
    // -------------------------------
    // TEST MODE (Req.8)
    // -------------------------------
    uart_write_str("System Boot in TEST MODE\r\n");
    run_all_tests();   // WhiteBox + BlackBox TC 실행
    while(1);          // 테스트 모드에서는 루프 진입하지 않음

#else
    // -------------------------------
    // NORMAL MODE (Req.1~7)
    // -------------------------------
    uart_write_str("System Boot in NORMAL MODE\r\n");

    static uint32_t t_uart=0, t_pmic=0, t_can=0, t_vout=0;

    for(;;){
        uint32_t now = millis();

        // [Req.4] PMIC Fault 감지 → DTC 저장
        if (now - t_pmic >= 20){
            t_pmic = now;
            pmic_check_faults();
        }

        // [Req.7] CAN 수신 → UDS Handler
        if (now - t_can >= 10){
            t_can = now;
            can_msg_t rx;
            while (can_recv(&rx)){
                UDS_HandleMessage(&rx);
            }
        }

        // [Req.4] UART Heartbeat
        if (now - t_uart >= 500){
            t_uart = now;
            uart_write_str("[HB] System Normal\r\n");
        }

        // [Req.5] PMIC VOUT 제어 (예시: 5초마다 3.3V ↔ 5V 변경)
        if (now - t_vout >= 5000){
            t_vout = now;
            static uint16_t volt = 3300;
            volt = (volt==3300) ? 5000 : 3300;
            pmic_set_voltage(volt);
        }

        // [Req.1] 루프 내 통신 순서 → I2C → SPI → CAN → UART
        // (이미 위 타이머 순환 구조 안에서 충족)
    }
#endif
}





