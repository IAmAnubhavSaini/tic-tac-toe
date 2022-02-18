cmake_minimum_required(VERSION 3.21)
project(tic_tac_toe C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(tic_tac_toe
        src/main.c
        )
