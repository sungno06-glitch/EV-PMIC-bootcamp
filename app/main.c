#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "../include/app_config.h"

#ifdef _WIN32
  #include <windows.h>
  static void msleep(unsigned ms){ Sleep(ms); }
#else
  #include <unistd.h>
  static void msleep(unsigned ms){ usleep(ms*1000); }
#endif

// 현재 시간(ms)
static uint64_t now_ms(void){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec*1000ULL + ts.tv_nsec/1000000ULL;
}

// 각 슬롯 더미 작업
static void task_i2c(void){  printf("[I2C]  poll PMIC status\n"); }
static void task_spi(void){  printf("[SPI]  EEPROM service\n"); }
static void task_can(void){  printf("[CAN]  service UDS requests\n"); }
static void task_uart(void){ printf("[UART] heartbeat: System OK\n"); }

int main(void){
    printf("Boot OK (Beginner: I2C -> SPI -> CAN -> UART)\n");

    uint64_t t0_uart=0, t0_i2c=0, t0_spi=0, t0_can=0;

    for(;;){
        uint64_t now = now_ms();

        if (now - t0_i2c >= I2C_POLL_MS){ t0_i2c = now; task_i2c(); }
        if (now - t0_spi >= SPI_IDLE_MS){ t0_spi = now; task_spi(); }
        if (now - t0_can >= CAN_SERVICE_MS){ t0_can = now; task_can(); }
        if (now - t0_uart >= UART_HEARTBEAT_MS){ t0_uart = now; task_uart(); }

        msleep(5);
    }
    return 0;
}
