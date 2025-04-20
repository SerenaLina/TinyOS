#ifndef _STACK_H
#define _STACK_H

extern char stack_start;
extern char stack_end;

extern char *stack_ptr;

void stack_init(void);

char* get_sp(void);

unsigned long get_stack_usage(void);

#endif