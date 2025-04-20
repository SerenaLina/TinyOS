cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain.cmake)

project(TinyOS C ASM)

# 编译选项
add_compile_options(-g -nostdlib -nostartfiles -mcmodel=medany)
include_directories(${CMAKE_SOURCE_DIR})

set(SOURCES
    bootasm.S
    src/main.c
    src/uart.c
    src/shell.c
    src/disk.c
)

add_executable(bootloader.elf ${SOURCES})

# 链接选项
target_link_options(bootloader.elf PRIVATE 
    -T ${CMAKE_SOURCE_DIR}/linked.ld 
    -nostdlib 
    -nostartfiles
    -static
    -Wl,--gc-sections
)