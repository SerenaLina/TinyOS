#include "./include/shell.h"

static const struct shell_cmd shell_cmds[] = {
    {"help", cmd_help, "Display help information."},
    {"clear", cmd_clear, "Clear the screen."},
    {"info", cmd_info, "Display system information."}, 
    {"disk", cmd_disk, "Disk operation."},
    {0, 0, 0}
};



void shell_init(void) {
    uart_puts("\n\rTinyOS Shell v0.1\n\r");
    uart_puts(">> ");
}

void shell_run(void) {
    char c;
    char buf[128];
    int i = 0;
    while(1) {
        c = getc();
        if(c == '\r' || c == '\n') {
            buf[i] = '\0';
            i = 0;
            uart_puts("\n\r");
            excute_cmd(buf);
            uart_puts(">> ");
        }
        else if((c == '\b' || c == 127) && i > 0) {
            i--;
            uart_putc('\b');
            uart_putc(' ');
            uart_putc('\b');
        }
        else if(i < sizeof(buf) - 1) {
            buf[i++] = c;
            uart_putc(c);
        }
    }
}

int strcmp(const char *s1, const char *s2) {
    while(*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void cmd_help(void) {
    for(const struct shell_cmd *p = shell_cmds; p->name; p++) {
        uart_puts(p->name);
        uart_puts(": ");
        uart_puts(p->desc);
        uart_puts("\n\r");
    }
}

void excute_cmd(char *cmd) {
    for(const struct shell_cmd *p = shell_cmds; p->name; p++) {
        if(strcmp(cmd, p->name) == 0) {
            p->func();
            return;
        }
    }
    if(cmd[0] != '\0') {
        uart_puts("Unknown command: ");
        uart_puts(cmd);
        uart_puts("\n\r");
    }
}

void cmd_clear(void) {
    uart_puts("\x1b[2J");
    uart_puts("\x1b[H");
}

void cmd_info(void) {
    uart_puts("System Information:\n\r");
    uart_puts("TinyOS v0.1\n\r");
    uart_puts("CPU: ARMv7\n\r");
    uart_puts("Memory: 128KB\n\r");
}

void cmd_disk(void)
{
    // Hope to fix it.Capacity is 00000000 :(
    volatile uint64_t *capacity = (uint64_t *)(VIRTIO_BLK_BASE + VIRTIO_REG_CONFIG + VIRTIO_BLK_CONFIG_CAPACITY);
    uint64_t bytes = *capacity * 512;
    volatile unsigned int *magic = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_MAGIC);
    volatile unsigned int *version = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_VERSION);
    volatile unsigned int *device_id = (unsigned int *)(VIRTIO_BLK_BASE + VIRTIO_REG_DEVICE_ID);
    uart_puts("Disk Capacity: ");

    uart_puthex((uint32_t)(*capacity >> 32));
    uart_puthex((uint32_t)(*capacity));
    uart_puts(" sectors\n\r");

    uart_puts("Total Size: ");
    if (bytes >= 1024*1024*1024) {
        uart_puthex((uint32_t)(bytes / (1024*1024*1024)));
        uart_puts(" GB\n\r");
    } else if (bytes >= 1024*1024) {
        uart_puthex((uint32_t)(bytes / (1024*1024)));
        uart_puts(" MB\n\r");
    } else if (bytes >= 1024) {
        uart_puthex((uint32_t)(bytes / 1024));
        uart_puts(" KB\n\r");
    } else {
        uart_puthex((uint32_t)bytes);
        uart_puts(" bytes\n\r");
    }
    uart_puts("Disk Operation:\n\r");
    uart_puts("Status:");
    uart_puts(*magic == 0x74726976 ? "OK\n\r" : "Failed\n\r");
    uart_puts("Version:");
    uart_puts(*version == 0x00000001 || 0x00000002? "OK\n\r" : "Failed\n\r");
    uart_puts("Device ID:");
    uart_puts(*device_id == 0x00000000? "OK\n\r" : "Failed\n\r");


}