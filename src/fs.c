#include "./include/fs.h"

/*
TODO:fs_create(char *filename, int size)
*/

static struct superblock sb;
int fs_init() {
    disk_read(&sb, 0, 1);
    if(sb.magic != 0x4D494E49)
    {
        sb.magic = 0x4D494E49;
        sb.total_blocks = 65536;
        sb.free_blocks = 65530;
        sb.block_size = 512;
        disk_write(&sb, 0, 1);
    }

    struct dir_entry entries[128] = {0};
    disk_write(entries, 1, DIR_ENTRY_SECTORS);
    return 0;
}

int fs_list()
{
    struct dir_entry entries[128];
    disk_read(entries, 1, DIR_ENTRY_SECTORS);
    for(int i = 0; i < 128; i++)
    {
        if(entries[i].filename[0] != '\0')
        {
            uart_puts(entries[i].filename);
            uart_puts("- Size:");
            uart_puthex(entries[i].file_size);
            uart_puts(" Bytes\n");
        }
    }
    return 0;
}
int fs_read(const char *filename, void *buf, int size)
{
    struct dir_entry entries[128];
    disk_read(entries, 1, DIR_ENTRY_SECTORS);
    for(int i = 0; i < 128; i++)
    {
        if(strcmp(entries[i].filename, filename) == 0)
        {
            int sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
            disk_read(buf, entries[i].start_block, sectors);
            uart_puts((char*)buf);
            return 0;
        }
    }
    uart_puts("File not found\n");
    return -1; //file not found
}

//MAKE SURE THE COUTN IS RIGHT.
int fs_write(const char *filename, void *buf, int size)
{
    struct dir_entry entries[128];
    disk_read(entries, 1, DIR_ENTRY_SECTORS);
    for(int i = 0; i < 128; i++)
    {
        if(strcmp(entries[i].filename, filename) == 0)
        {
            int sectors = (size + SECTOR_SIZE - 1) / SECTOR_SIZE;
            disk_write(buf, entries[i].start_block, sectors);
            return 0;
        }
    }
    uart_puts("File not found\n");
    return -1; //file not found
}


