#include "board.h"

// ▷ 실제 타겟에서 SysTick ISR에서 ++g_ms 하세요
static volatile uint32_t g_ms = 0;

void board_init_clock_gpio(void){ /* TODO: MCU 클럭/GPIO 설정 */ }
void board_init_systick_1ms(void){ /* TODO: 1ms SysTick 설정 */ }
uint32_t millis(void){ return g_ms; }

// 예: 타겟의 SysTick_Handler()에서 g_ms++ 호출 필요
// void SysTick_Handler(void){ g_ms++; /* HAL_IncTick(); 등 */ }
