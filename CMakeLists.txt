cmake_minimum_required(VERSION 3.21)
project(minitalk C)

set(CMAKE_C_STANDARD 99)

#add_executable(minitalk client.c)
add_executable(minitalk server.c)
