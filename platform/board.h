#ifndef BOARD_H
#define BOARD_H
#include <stdint.h>

void board_init_clock_gpio(void);
void board_init_systick_1ms(void);
uint32_t millis(void);

#endif
