#ifndef _UART_H
#define _UART_H

#include "types.h"

#define UART0 0x10000000
#define UART_THR ((volatile uint8_t *)(UART0 + 0x00))
#define UART_RBR ((volatile uint8_t *)(UART0 + 0x00))
#define UART_LSR ((volatile uint8_t *)(UART0 + 0x05))

void init_uart(void);
void uart_putc(char c);
void uart_puts(const char *s);
void uart_puthex(unsigned int hex); //debug
char getc(void);

#endif