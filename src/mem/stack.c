#include "../include/stack.h"

void stack_init(void)
{
    __asm__ volatile("la sp,stack_end");
}

char* get_sp(void)
{
    char *sp;
    __asm__ volatile("mv %0,sp":"=r"(sp));
    return sp;
}

unsigned long get_stack_usage(void)
{
    char *sp=get_sp();
    return (unsigned long)(&stack_end)-sp;
}

