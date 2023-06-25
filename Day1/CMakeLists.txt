cmake_minimum_required(VERSION 3.25)
project(Day1 C)

set(CMAKE_C_STANDARD 11)

include_directories(HeaderFile)
add_executable(Day1 main.c HeaderFile/socketclient.h ResourceFile/socketclient.c)
