#ifndef FS_H
#define FS_H
#include "types.h"
#include "uart.h"
#include "shell.h"

#define SECTOR_SIZE 512
#define DIR_ENTRY_NUM 128
#define DIR_ENTRY_SECTORS ((sizeof(struct dir_entry) * DIR_ENTRY_NUM + SECTOR_SIZE - 1) / SECTOR_SIZE)
int fs_init(void);
int fs_read(const char *filename,void *buf, int size);
int fs_write(const char *filename,void *buf, int size);
int fs_list(void);

struct superblock{
    uint32_t magic;
    uint32_t total_blocks;
    uint32_t free_blocks;
    uint32_t block_size;
}

struct dir_entry{
    char filename[32];
    uint32_t file_size;
    uint32_t type;
    uint32_t start_block;
}

#endif