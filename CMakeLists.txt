cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

set(CMAKE_C_COMPILER "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi")

project(week06 C CXX ASM)

pico_sdk_init()

add_executable(out morse_code.c)
target_link_libraries(out pico_stdlib)

