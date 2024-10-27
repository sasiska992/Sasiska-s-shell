cmake_minimum_required(VERSION 3.28)
project(lesson_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lesson_2
        shell.cpp
        main.cpp
        main.h
        test.cpp
        test.h)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(lesson_2 ${CURSES_LIBRARIES})
