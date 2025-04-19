#include <stdint.h>

extern char bss_start;
extern char bss_end;

#define UART0 0x10000000
#define UART_THR ((volatile uint8_t *)(UART0 + 0x00))
#define UART_RBR ((volatile uint8_t *)(UART0 + 0x00))
#define UART_LSR ((volatile uint8_t *)(UART0 + 0x05))

static void init_uart(void);
static void uart_putc(char c);
static void uart_puts(const char *s);
static char getc(void);
static void shell_init(void);
static void shell_run(void);

void main(void) {
    init_uart();
    uart_puts("TinyOS is booting...\n");

    shell_init();
    shell_run();
    while(1) {
        __asm__ volatile("wfi");
    }
}

static void init_uart(void) {} //need to do nothing,as QEMU has already done it

static void uart_putc(char c) {
    while((*UART_LSR & (1 << 5)) == 0)
        ;
    *UART_THR = c;
}

static void uart_puts(const char *s) {
    while(*s) {
        uart_putc(*s++); //put char and move pointer
    }
}

static char getc(void) {
    while((*UART_LSR & (1 << 0)) == 0)
        ;
    return *UART_RBR;
}

static void shell_init(void) {
    uart_puts("\n\rTinyOS Shell v0.1\n\r");
    uart_puts(">> ");
}

static void shell_run(void) {
    char c;
    char buf[128];
    int i = 0;
    while(1) {
        c = getc();
        if(c == '\r' || c == '\n') {
            buf[i] = '\0';
            i = 0;
            uart_puts("\n\r");
            //Execute code here.
            uart_puts(">> ");
        }
        else if(c == '\b' && i > 0) {
            i--;
            uart_puts("\b"); 
            uart_puts(" ");
            uart_puts("\b");
        }
        else if(i < sizeof(buf) - 1) {
            buf[i++] = c;
            uart_putc(c);
        }
    }
}
