cmake_minimum_required(VERSION 3.29)
project(HW1_BetterC)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW1_BetterC main.cpp
        VectorDouble.cpp
        VectorDouble.h
        Dict.cpp
        Dict.h
        Calculator.cpp
        Calculator.h
)
