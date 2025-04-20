@echo off

:: 创建磁盘映像（如果不存在）
if not exist disk.img (
    fsutil file createnew disk.img 33554432
)

:: 启动QEMU调试模式
start qemu-system-riscv64 -machine virt -m 128M ^
    -drive file=disk.img,if=virtio,format=raw ^
    -kernel bootloader.elf ^
    -nographic ^
    -bios none ^
    -S -s

:: 等待QEMU启动
timeout /t 2

:: 启动GDB并连接到QEMU
riscv64-unknown-elf-gdb bootloader.elf ^
    -ex "target remote localhost:1234" ^
    -ex "set $pc=0x80200000" ^
    -ex "break main" ^
    -ex "continue"