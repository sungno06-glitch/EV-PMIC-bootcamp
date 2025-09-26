#include "uart_poll.h"
#include <stdio.h>

// ▷ 폴링 방식: printf 리다이렉트 or HAL_UART_Transmit polling 대체
void uart_init_poll(void){ /* TODO: UART 초기화 (115200/8N1 등) */ }
void uart_write_str(const char *s){ printf("%s", s); }
