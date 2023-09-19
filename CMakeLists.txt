cmake_minimum_required(VERSION 3.26)
project(kiwios C)

set(CMAKE_C_STANDARD 11)

add_executable(kiwios
        src/kernel.c)
