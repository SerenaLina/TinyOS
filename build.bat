@echo off

:: 清理旧的构建文件
if exist build (
    rmdir /s /q build
)
mkdir build
cd build

:: 配置和构建项目
cmake -G "Ninja" ..
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    cd ..
    exit /b 1
)

ninja
if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    cd ..
    exit /b 1
)

echo Build successful!
cd ..

:: 创建32MB的磁盘映像（如果不存在）
if not exist disk.img (
    fsutil file createnew disk.img 33554432
    echo Created new disk image
)

:: 运行QEMU
qemu-system-riscv64 -machine virt -m 128M -drive file=disk.img,if=virtio,format=raw -nographic