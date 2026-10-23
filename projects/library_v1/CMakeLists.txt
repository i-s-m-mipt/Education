##########################################################################

cmake_minimum_required(VERSION 3.28)

##########################################################################

project(static VERSION 24.02.06 LANGUAGES CXX)

##########################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS OFF)

##########################################################################

add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wall;-Wextra;-Wpedantic>")

##########################################################################

add_library            (static STATIC source/06.19.cpp)

target_compile_options (static PRIVATE -O0)

##########################################################################