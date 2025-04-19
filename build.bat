@echo off
riscv64-unknown-elf-gcc -g -T linked.ld -nostdlib -nostartfiles -mcmodel=medany bootasm.S main.c -o bootloader.elf
if %ERRORLEVEL% EQU 0 (
    echo Build successful!
) else (
    echo Build failed!
    exit /b 1
)