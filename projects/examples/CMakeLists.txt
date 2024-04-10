cmake_minimum_required(VERSION 3.27)

project(examples VERSION 24.02.06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost         1.84 REQUIRED COMPONENTS filesystem locale log python system unit_test_framework)
find_package(Python3       3.11 REQUIRED COMPONENTS Interpreter Development)
find_package(nlohmann_json 3.11 REQUIRED COMPONENTS)
find_package(GTest         1.14 REQUIRED COMPONENTS)
find_package(benchmark          REQUIRED COMPONENTS)

include_directories(        ${Boost_INCLUDE_DIRS})
include_directories(      ${Python3_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(        ${GTEST_INCLUDE_DIRS})
include_directories(    ${benchmark_INCLUDE_DIRS})

set(debug
#   01.01.introduction
    01.02.introduction.function.main
    01.03.introduction.standard
#   01.04.project.tool.git
    02.01.statement.expression.variable.type
    02.02.statement.expression.operator
    02.03.statement.selection
    02.04.statement.iteration.jump
    02.05.pointer
    02.06.pointer.array
    02.07.pointer.array.new.delete
    02.08.container.vector
    02.09.reference.lvalue
    02.10.function
    02.11.algorithm.binary.search
    02.12.algorithm.lexicographic.order
    02.13.algorithm.insertion.merge.sorting
    03.01.class.structure
    03.02.class
    03.03.class.friend
    03.04.pattern.attorney.client.passkey
    03.05.class.association
    03.06.class.inheritance
    03.07.class.inheritance.multiple
#   03.08.class.inheritance.multiple.diamond
    03.09.class.polymorphism
#   03.10.class.polymorphism.vptr.vtbl
    03.11.class.polymorphism.type.covariant
    03.12.class.polymorphism.type.identification
    03.13.class.optimization
#   03.14.expression.classification
    03.15.reference.lvalue.rvalue
    03.16.reference.lvalue.rvalue.function.overload
    03.17.implementation.container.vector
    03.18.class.operator.overload
    03.19.class.operator.overload.output
    03.20.class.operator.overload.spaceship
    03.21.class.operator.overload.optimization
    04.01.template.function
    04.02.template.function.variadic
    04.03.template.function.variadic.tree.traversal
    04.04.template.class
    04.05.template.class.friend
    04.06.template.alias.variable
    04.07.metaprogramming
    04.08.metaprogramming.constexpr
    04.09.metaprogramming.constexpr.hybrid.ratio
    05.01.pattern.builder
    05.02.pattern.factory
    05.03.pattern.prototype
    05.04.pattern.singleton.monostate.noncopyable
    05.05.pattern.adapter
    05.06.pattern.bridge
    05.07.pattern.composite
    05.08.pattern.decorator
    05.09.pattern.memento
    05.10.pattern.observer
    05.11.pattern.state
    05.12.pattern.strategy
    05.13.pattern.template.method
    05.14.template.polymorphism
    05.15.pattern.crtp
    05.16.pattern.crtp.observer
    05.17.pattern.crtp.operator.overload
    05.18.pattern.crtp.mixin
    05.19.pattern.crtp.mixin.constructor
    05.20.pattern.crtp.mixin.inheritance.variadic
06.01.reference.forwarding
06.02.pattern.sfinae
06.03.template.inference
06.04.implementation.type.trait
06.05.implementation.type.concept
06.06.implementation.type.list
06.07.implementation.tuple
06.08.metaprogramming.algorithm.cartesian
)

set(release
)

foreach(entry IN LISTS debug)
    add_executable        (${entry} source/${entry}.cpp)
    target_link_libraries (${entry} PRIVATE ${Boost_LIBRARIES})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
endforeach()

foreach(entry IN LISTS release)
    add_executable        (${entry} source/${entry}.cpp)
    target_link_libraries (${entry} PRIVATE ${Boost_LIBRARIES})
    target_link_libraries (${entry} PRIVATE benchmark::benchmark)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O3) 
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
endforeach()

set(section_07 source/section_07/)

set(sources_07
    empty_function
    pimpl_idiom)

foreach(entry IN LISTS sources_07)
    add_executable        (${entry} ${section_07}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

add_executable            (libraries_test ${section_07}libraries_test.cpp)
target_include_directories(libraries_test PRIVATE ${CMAKE_SOURCE_DIR}/../library_v1/source/)
target_link_libraries     (libraries_test PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/library_v1/liblibrary_v1.a)
target_link_libraries     (libraries_test PRIVATE ${Boost_LIBRARIES})
set_target_properties     (libraries_test PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options    (libraries_test PRIVATE -Wall -pedantic -O0) 

add_executable           (project ${section_07}project_main.cpp ${section_07}project_source.cpp)
target_precompile_headers(project PRIVATE ${section_07}precompiled.hpp)
set_target_properties    (project PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options   (project PRIVATE -Wall -pedantic -O0) 

set(section_08 source/section_08/)

set(sources_08
    errors_handling
    exception_basics
    optional_basics
    stack_interface
    union_basics
    variant_basics)

foreach(entry IN LISTS sources_08)
    add_executable        (${entry} ${section_08}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

add_executable        (boost_logging ${section_08}boost_logging.cpp)
target_link_libraries (boost_logging PRIVATE ${Boost_LIBRARIES})
set_target_properties (boost_logging PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(boost_logging PRIVATE -Wall -pedantic -O0) 

add_executable        (boost_testing ${section_08}boost_testing.cpp)
target_link_libraries (boost_testing PRIVATE ${Boost_LIBRARIES})
set_target_properties (boost_testing PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(boost_testing PRIVATE -Wall -pedantic -O0) 

add_executable        (google_benchmark ${section_08}google_benchmark.cpp)
target_link_libraries (google_benchmark PRIVATE benchmark::benchmark)
set_target_properties (google_benchmark PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(google_benchmark PRIVATE -Wall -pedantic -O3)

add_executable        (google_testing ${section_08}google_testing.cpp)
target_link_libraries (google_testing PRIVATE ${GTEST_BOTH_LIBRARIES})
set_target_properties (google_testing PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(google_testing PRIVATE -Wall -pedantic -O0) 

set(section_09 source/section_09/)

set(sources_09
    advanced_constants
    advanced_literals
    calendar_time_zones
    chrono_management
    floating_point_types
    multiprecision_float
    complex_numbers
    binary_gray_code
    indian_algorithm)

foreach(entry IN LISTS sources_09)
    add_executable        (${entry} ${section_09}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(sources_09_release
    random_generation
    inscribed_simplex
    bitwise_operations)

foreach(entry IN LISTS sources_09_release)
    add_executable        (${entry} ${section_09}${entry}.cpp)
    target_link_libraries (${entry} PRIVATE benchmark::benchmark)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O3)
endforeach()

set(section_10 source/section_10/)

set(sources_10
    bad_allocations
    custom_optional
    custom_shared_ptr
    custom_unique_ptr
    iterator_basics
    iterator_facade
    memory_resource
    pattern_facade
    pattern_iterator
    shared_from_this
    smart_pointers
    standard_allocator
    arena_adaptor)

foreach(entry IN LISTS sources_10)
    add_executable        (${entry} ${section_10}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set (sources_10_release
    placement_new
    data_alignment
    arena_allocator
    stack_allocator
    chain_allocator
    block_allocator
    noheap_allocator)

foreach(entry IN LISTS sources_10_release)
    add_executable        (${entry} ${section_10}${entry}.cpp)
    target_link_libraries (${entry} PRIVATE benchmark::benchmark)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O3)
endforeach()

set(section_11 source/section_11/)

set(sources_11
    circular_buffer
    container_adaptors
    container_basics
    container_lists
    custom_hash_equal
    filling_multiarray
    hash_functions
    hash_table_basics
    multidimensionals
    multiple_interfaces
    pattern_flyweight
    vector_bool_proxy
    stack_with_minimum
    common_subsequence
    numeric_valarrays)

foreach(entry IN LISTS sources_11)
    add_executable        (${entry} ${section_11}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(sources_11_release
    sorting_compare
    container_trees
    vectors_matrices)

foreach(entry IN LISTS sources_11_release)
    add_executable        (${entry} ${section_11}${entry}.cpp)
    target_link_libraries (${entry} PRIVATE benchmark::benchmark)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O3) 
endforeach()

set(section_14 source/section_14/)

set(sources_14
    iostream_iterators
    variadic_output)

foreach(entry IN LISTS sources_14)
    add_executable        (${entry} ${section_14}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_16 source/section_16/)

set(sources_16
    process_handler
    process_manager)

foreach(entry IN LISTS sources_16)
    add_executable        (${entry} ${section_16}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_18 source/section_18/)

set(sources_18
    long_arithmetic
    multiprecision_int)

foreach(entry IN LISTS sources_18)
    add_executable        (${entry} ${section_18}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

add_executable        (python_caller ${section_18}python_caller.cpp ${section_18}python_wrapper.cpp)
target_link_libraries (python_caller PRIVATE   ${Boost_LIBRARIES})
target_link_libraries (python_caller PRIVATE ${Python3_LIBRARIES})
set_target_properties (python_caller PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(python_caller PRIVATE -Wall -pedantic -O0) 