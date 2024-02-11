cmake_minimum_required(VERSION 3.19)
project(PuissanceN_IFB C)

set(CMAKE_C_STANDARD 99)

add_executable(PuissanceN_IFB main.c PuissanceN.h IA.c check.c grid.c files.c game.c)