cmake_minimum_required(VERSION 3.23)
project(A1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(A1
        src/test.txt
        main.c
        tokens.h)
