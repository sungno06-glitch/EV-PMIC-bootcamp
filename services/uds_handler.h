#ifndef UDS_HANDLER_H
#define UDS_HANDLER_H

#include "../drivers/can/can_isr.h"

void UDS_HandleMessage(const can_msg_t *rx);

#endif
