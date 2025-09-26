#include "uds_handler.h"
#include "dtc_manager.h"
#include <stdio.h>
#include <string.h>

// UDS Service IDs
#define UDS_READ_DTC   0x19
#define UDS_CLEAR_DTC  0x14
#define UDS_WRITE_DID  0x2E

// 예시 DID
#define DID_TEST_PARAM 0x1234

static uint16_t test_param = 0xABCD;

void UDS_HandleMessage(const can_msg_t *rx){
    can_msg_t tx;
    memset(&tx, 0, sizeof(tx));
    tx.id = 0x7E8; // ECU 응답 ID

    switch(rx->data[0]){
        case UDS_READ_DTC: {
            uint16_t dtcs[8];
            uint8_t n = DTC_ReadAll(dtcs, 8);

            tx.len = n*2 + 1;
            tx.data[0] = UDS_READ_DTC;
            for (int i=0; i<n; i++){
                tx.data[1+i*2] = (dtcs[i]>>8) & 0xFF;
                tx.data[2+i*2] = dtcs[i] & 0xFF;
            }
            (void)can_send(&tx);
            printf("UDS: ReadDTC %d codes sent\n", n);
        } break;

        case UDS_CLEAR_DTC: {
            DTC_ClearAll();
            tx.len = 1;
            tx.data[0] = UDS_CLEAR_DTC;
            (void)can_send(&tx);
            printf("UDS: DTC Cleared\n");
        } break;

        case UDS_WRITE_DID: {
            // 예: DID=0x1234, 데이터=2바이트
            if (rx->len >= 4){
                uint16_t did = (rx->data[1]<<8) | rx->data[2];
                if (did == DID_TEST_PARAM){
                    test_param = (rx->data[3]<<8) | rx->data[4];
                    printf("UDS: WriteDID DID=0x%04X, value=0x%04X\n", did, test_param);
                    tx.len = 3;
                    tx.data[0] = UDS_WRITE_DID;
                    tx.data[1] = rx->data[1];
                    tx.data[2] = rx->data[2];
                    (void)can_send(&tx);
                }
            }
        } break;

        default:
            printf("UDS: Unknown Service 0x%02X\n", rx->data[0]);
            break;
    }
}

