####################################################################

cmake_minimum_required(VERSION 3.28)

####################################################################

project(static VERSION 24.02.06 LANGUAGES CXX)

####################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

####################################################################

find_package(Boost 1.85 REQUIRED COMPONENTS)

####################################################################

include_directories(${Boost_INCLUDE_DIRS})

####################################################################

add_library            (static STATIC source/06.03.03.cpp)

target_compile_options (static PRIVATE -Wall -Wextra -Wpedantic -O0)

####################################################################