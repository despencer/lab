cmake_minimum_required(VERSION 3.15)

project(dynshar VERSION 1.0)

add_compile_options(-Wall -Werror)
add_executable(dynshar main.cpp)
add_library(first SHARED first.cpp)
add_library(second SHARED second.cpp)

