OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
    BOOT_ROM(rx) : ORIGIN = 0x80000000, LENGTH = 64K
    RAM(rwx) : ORIGIN = 0x80010000, LENGTH = 128M
}

SECTIONS
{
    .text : {
        *(.text.init)
        *(.text)
        *(.text.*)
    } > BOOT_ROM

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    } > BOOT_ROM

    .data : {
        . = ALIGN(8);
        *(.data)
        *(.data.*)
    } > RAM AT > BOOT_ROM

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