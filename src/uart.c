#include "./include/uart.h"

void init_uart(void) {} //need to do nothing,as QEMU has already done it

void uart_putc(char c) {
    while((*UART_LSR & (1 << 5)) == 0)
        ;
    *UART_THR = c;
}

void uart_puts(const char *s) {
    while(*s) {
        uart_putc(*s++); //put char and move pointer
    }
}

char getc(void) {
    while((*UART_LSR & (1 << 0)) == 0)
        ;
    return *UART_RBR;
}