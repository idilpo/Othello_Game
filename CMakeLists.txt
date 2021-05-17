cmake_minimum_required(VERSION 3.17)
project(Othello_Game C)

set(CMAKE_C_STANDARD 11)

add_executable(Othello_Game main.c functions.c header.h)