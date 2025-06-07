cmake_minimum_required(VERSION 3.14)

project(ContestX_skeleton CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

add_executable(A1       A1/main.cpp
                        A1/sortingAlgorithms.hpp
                        A1/stringGenerator.hpp
                        A1/stringSortTester.hpp)
add_executable(A1m      A1m/main.cpp)
add_executable(A1q      A1q/main.cpp)
add_executable(A1r      A1r/main.cpp)
add_executable(A1rq     A1rq/main.cpp)
add_executable(P1       P1/main.cpp)
add_executable(P2       P2/main.cpp)
add_executable(P3       P3/main.cpp)