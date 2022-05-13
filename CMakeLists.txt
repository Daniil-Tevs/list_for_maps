cmake_minimum_required(VERSION 3.20)
project(list_for_maps)

set(CMAKE_CXX_STANDARD 14)
include_directories("inc/")
include_directories("src/")
add_executable(list_for_maps main.cpp inc/classes.h src/classes.cpp)
