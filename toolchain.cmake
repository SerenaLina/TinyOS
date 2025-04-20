set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv64)

# Toolchain paths
set(TOOLCHAIN_PATH "D:/nuclei_riscv_newlibc_prebuilt_win32_2025.02/gcc/bin")
set(CMAKE_MAKE_PROGRAM "D:/ninja-win/ninja.exe" CACHE FILEPATH "Path to Ninja build tool")

# Compilers
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/riscv64-unknown-elf-gcc.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/riscv64-unknown-elf-gcc.exe")

# 添加交叉编译设置
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Disable compiler checks
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)