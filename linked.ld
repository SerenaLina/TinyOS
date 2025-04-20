OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    RAM(rwx) : ORIGIN = 0x80200000, LENGTH = 128M
}

SECTIONS
{
    .text : {
        *(.text.init)
        *(.text)
        *(.text.*)
    } > RAM

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > RAM

    .data : {
        . = ALIGN(8);
        *(.data)
        *(.data.*)
    } > RAM

    .bss : {
        . = ALIGN(8);
        bss_start = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)
        . = ALIGN(8);
        bss_end = .;
    } > RAM
}

PROVIDE(bss_start = bss_start);
PROVIDE(bss_end = bss_end);