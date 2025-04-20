#ifndef _SHELL_H
#define _SHELL_H

#include "types.h"
#include "uart.h"
#include "disk.h"

struct shell_cmd {
    const char *name;
    void (*func)(void);
    const char *desc;
};


void shell_init(void);
void shell_run(void);


void cmd_help(void);
void cmd_clear(void);
void cmd_info(void);
void cmd_disk(void);
void excute_cmd(char *cmd);

int strcmp(const char *s1, const char *s2);

#endif