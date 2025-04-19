@echo off
start qemu-system-riscv64 -machine virt -nographic -bios none -kernel bootloader.elf -S -s
riscv64-unknown-elf-gdb bootloader.elf -ex "target remote localhost:1234" -ex "break _start" -ex "continue"