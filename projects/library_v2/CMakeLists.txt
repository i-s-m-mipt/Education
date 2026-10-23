##########################################################################

cmake_minimum_required(VERSION 3.28)

##########################################################################

project(shared VERSION 24.02.06 LANGUAGES CXX)

##########################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_EXTENSIONS OFF)

##########################################################################

add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-Wall;-Wextra;-Wpedantic>")

##########################################################################

set(Boost_USE_STATIC_LIBS    ON)

set(Boost_USE_STATIC_RUNTIME ON)

##########################################################################

find_package(Boost 1.90 REQUIRED COMPONENTS)

##########################################################################

include_directories(${Boost_INCLUDE_DIRS})

##########################################################################

add_library            (shared SHARED source/06.20.cpp)

target_compile_options (shared PRIVATE -O0)

##########################################################################