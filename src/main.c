#include "./include/uart.h"
#include "./include/types.h"
#include "./include/shell.h"
#include "./include/disk.h"
extern char bss_start;
extern char bss_end;


void main(void) {
    init_uart();
    uart_puts("TinyOS is booting...\n");

    disk_init();
    uart_puts("Disk init done\n");

    shell_init();
    shell_run();
    while(1) {
        __asm__ volatile("wfi");
    }
}


