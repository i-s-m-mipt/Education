cmake_minimum_required(VERSION 3.14)
project(HybridSortTest)

set(CMAKE_CXX_STANDARD 20)

# Находим GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исполняемый файл
add_executable(hybrid_sort_test
  tests.cpp
  main.cpp
)

# Подключаем GoogleTest
target_link_libraries(hybrid_sort_test
  GTest::gtest GTest::gtest_main
)

# Добавляем тесты
gtest_discover_tests(hybrid_sort_test)