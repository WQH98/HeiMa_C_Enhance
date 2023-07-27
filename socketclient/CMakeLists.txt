cmake_minimum_required(VERSION 3.26)
project(socketclient C)

set(CMAKE_C_STANDARD 11)

add_executable(socketclient main.c
        socketclient/socketclient.c
        socketclient/socketclient.h)
include_directories(socketclient)