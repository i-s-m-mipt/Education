cmake_minimum_required(VERSION 3.27)

project(library_v1 VERSION 24.02.06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(x32 -m32)
set(x64 -m64)

find_package(Boost 1.84 REQUIRED COMPONENTS)

include_directories(${Boost_INCLUDE_DIRS})

add_library(library_v1 STATIC source/library.cpp)

set_target_properties(library_v1 PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})

target_compile_options(library_v1 PRIVATE -Wall -pedantic -O0)