cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER /usr/local/cross/bin/i686-elf-gcc)
set(CMAKE_ASM_COMPILER /usr/local/cross/bin/i686-elf-as)
set(CMAKE_C_FLAGS "-std=gnu99 -ffreestanding -O2 -Wall -Wextra -c")

project(testBoot C ASM)

set(CMAKE_C_STANDARD 99)

include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS "-O2 -nostdlib -T ../linker.ld -nostartfiles")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_LINKER /usr/local/cross/bin/i686-elf-ld)
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

add_executable(testBoot
        include/graphics.h
        include/terminal.h
        src/graphics.c
        src/kernel.c
        src/terminal.c
        src/boot.s
        fonts/font.o)

set_source_files_properties(
        fonts/font.o
        PROPERTIES
        EXTERNAL_OBJECT true
        GENERATED true
)
