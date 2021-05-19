cmake_minimum_required(VERSION 3.19)
project(rubixdream C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(rubixdream
        conio.c
        conio.h
        main.c
        rubixdream.c
        rubixdream.h)
