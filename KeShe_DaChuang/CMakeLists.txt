cmake_minimum_required(VERSION 3.7)
project(KeShe_DaChuang)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c schedule.h project.h people.h people.c project.c schedule.c)
add_executable(KeShe_DaChuang ${SOURCE_FILES})