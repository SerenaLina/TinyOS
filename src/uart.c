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

void uart_puthex(unsigned int hex) {
    uart_puts("0x");
    for(int i = 7; i >= 0; i--) {
        int h = (hex >> (i * 4)) & 0xf;
        if(h < 10)
            uart_putc('0' + h);
        else
            uart_putc('a' + h - 10);
    }
}