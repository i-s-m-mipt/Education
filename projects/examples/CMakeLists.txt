cmake_minimum_required(VERSION 3.27.4)

set(PROJECT_NAME examples VERSION 24.02.06 LANGUAGES CXX)

set(section_01 "source/section_01/")

add_executable(minimal_program ${section_01}minimal_program.cpp)