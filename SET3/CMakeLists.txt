cmake_minimum_required(VERSION 3.14)

project(ContestX_skeleton CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)

# the following options prevent compiler-optimization issues that are unwanted in an edu process
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

#### the list of targets ####

add_executable(P1 P1/main.cpp)
add_executable(P2 P2/main.cpp)
add_executable(P3 P3/main.cpp)
add_executable(P4 P4/main.cpp)
add_executable(P5 P5/main.cpp)
add_executable(P6 P6/main.cpp)
