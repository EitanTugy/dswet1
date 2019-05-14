cmake_minimum_required(VERSION 3.10)
project(dswet1)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS  "-std=c++11 -Wall")

add_executable(dswet1 library.cpp main.cpp)