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