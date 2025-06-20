cmake_minimum_required(VERSION 3.30)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(TicTacToe main.cpp
        choice_menu.cpp
        choice_menu.h
        interface.cpp
        interface.h
        "algorithm.h"
        algorithm.cpp)

target_link_libraries(TicTacToe sfml-graphics sfml-window sfml-system)