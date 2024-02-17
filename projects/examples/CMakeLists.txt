cmake_minimum_required(VERSION 3.27.4)

project(examples VERSION 24.02.06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(x32 -m32)
set(x64 -m64)

find_package(Boost   1.84 REQUIRED COMPONENTS filesystem log python system)
find_package(Python3 3.11 REQUIRED COMPONENTS Interpreter Development)

include_directories(  ${Boost_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})

set(sources_01 
    minimal_program
    standard_library)

foreach(entry IN LISTS sources_01)
    add_executable(${entry} source/section_01/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_02 
    bracket_sequences 
    combined_sorting 
    container_vector 
    dynamic_arrays 
    function_basics 
    iteration_basics 
    lvalue_references 
    operator_basics 
    optimized_search
    pointer_basics
    selection_basics
    static_arrays
    variable_basics)

foreach(entry IN LISTS sources_02)
    add_executable(${entry} source/section_02/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_03 
    associative_links
    attorney_client
    class_basics
    class_hierarchies
    class_optimizations
    covariant_types
    friendship_basics
    multiple_inheritance
    operator_overloading
    overload_resolution
    paired_operators
    rvalue_references
    special_functions
    structure_basics
    types_identification
    virtual_functions)

foreach(entry IN LISTS sources_03)
    add_executable(${entry} source/section_03/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_04
    class_templates
    constexpr_basics
    function_templates
    hybrid_durations
    metaprogramming
    special_templates
    template_friends
    variadic_templates
    variadic_traverse)

foreach(entry IN LISTS sources_04)
    add_executable(${entry} source/section_04/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_05
    crtp_basics
    crtp_counter
    crtp_operators
    mixin_basics
    mixin_initializer
    pattern_adapter
    pattern_bridge
    pattern_builder
    pattern_composite
    pattern_decorator
    pattern_factory
    pattern_memento
    pattern_observer
    pattern_prototype
    pattern_singleton
    pattern_state
    pattern_strategy
    pattern_template
    polymorphism
    spaceship_operator
    variadic_bases)

foreach(entry IN LISTS sources_05)
    add_executable(${entry} source/section_05/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_06
    types_inference)

foreach(entry IN LISTS sources_06)
    add_executable(${entry} source/section_06/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_07
    empty_function
    pimpl_idiom)

set(section_07 source/section_07/)

foreach(entry IN LISTS sources_07)
    add_executable(${entry} ${section_07}${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

add_executable(libraries_test ${section_07}libraries_test.cpp)
target_include_directories(libraries_test PRIVATE ${CMAKE_SOURCE_DIR}/../library_v1/source/)
target_link_libraries(libraries_test PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/library_v1/liblibrary_v1.a)
target_link_libraries(libraries_test PRIVATE ${Boost_LIBRARIES})
set_target_properties(libraries_test PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(libraries_test PRIVATE -Wall -pedantic -O0) # g++ --help=warnings

add_executable(project ${section_07}project_main.cpp ${section_07}project_source.cpp)
target_precompile_headers(project PRIVATE ${section_07}precompiled.hpp)
set_target_properties(project PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(project PRIVATE -Wall -pedantic -O0) # g++ --help=warnings

set(sources_08
    errors_handling
    exception_basics
    optional_basics
    stack_interface
    union_basics
    variant_basics)

set(section_08 source/section_08/)

foreach(entry IN LISTS sources_08)
    add_executable(${entry} ${section_08}${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

add_executable(custom_logger ${section_08}logger_examples.cpp ${section_08}custom_logger.cpp)
set_target_properties(custom_logger PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(custom_logger PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
target_link_libraries(custom_logger PRIVATE ${Boost_LIBRARIES})

add_executable(google_benchmarks ${section_08}google_benchmarks.cpp)
target_include_directories(google_benchmarks PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/benchmark/include)
target_link_libraries(google_benchmarks PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/benchmark/build/src/libbenchmark.a)
set_target_properties(google_benchmarks PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(google_benchmarks PRIVATE -Wall -pedantic -O3) # g++ --help=warnings
target_compile_definitions(google_benchmarks PRIVATE "NDEBUG")

set(sources_09
    advanced_constants
    advanced_literals
    bitwise_operations
    calendar_time_zones
    chrono_management
    floating_point_types
    multiprecision_float)

set(section_09 source/section_09/)

foreach(entry IN LISTS sources_09)
    add_executable(${entry} ${section_09}${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

add_executable(random_generation ${section_09}random_generation.cpp)
set_target_properties(random_generation PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(random_generation PRIVATE -Wall -pedantic -O3) # g++ --help=warnings

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
    placement_new
    shared_from_this
    smart_pointers
    standard_allocator)

    set(section_10 source/section_10/)

foreach(entry IN LISTS sources_10)
    add_executable(${entry} ${section_10}${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set (sources_10_release
    data_alignment
    arena_allocator
    stack_allocator
    chain_allocator)

foreach(entry IN LISTS sources_10_release)
    add_executable(${entry} ${section_10}${entry}.cpp)
    target_include_directories(${entry} PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/benchmark/include)
    target_link_libraries(${entry} PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/benchmark/build/src/libbenchmark.a)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O3) # g++ --help=warnings
    target_compile_definitions(${entry} PRIVATE "NDEBUG")
endforeach()

set(sources_11
    circular_buffer
    container_adaptors
    container_basics
    container_lists
    container_trees
    custom_hash_equal
    filling_multiarray
    hash_functions
    hash_table_basics
    multidimensionals
    multiple_interfaces
    pattern_flyweight
    vector_bool_proxy)

foreach(entry IN LISTS sources_11)
    add_executable(${entry} source/section_11/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_12
    advanced_visitors
    algorithms_on_graphs
    algorithms_on_ranges
    function_objects
    function_pointers
    heterogeneous_vector
    insert_iterators
    iostream_iterators
    lambda_expressions
    pattern_command
    pattern_visitor
    standard_algorithms)

foreach(entry IN LISTS sources_12)
    add_executable(${entry} source/section_12/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_14
    recursive_calculator)

foreach(entry IN LISTS sources_14)
    add_executable(${entry} source/section_14/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_16
    process_handler
    process_manager)

foreach(entry IN LISTS sources_16)
    add_executable(${entry} source/section_16/${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

set(sources_18
    long_arithmetic
    multiprecision_int)

set(section_18 source/section_18/)

foreach(entry IN LISTS sources_18)
    add_executable(${entry} ${section_18}${entry}.cpp)
    set_target_properties(${entry} PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) # g++ --help=warnings
endforeach()

add_executable(python_caller ${section_18}python_caller.cpp ${section_18}python_wrapper.cpp)

target_link_libraries(python_caller PRIVATE   ${Boost_LIBRARIES})
target_link_libraries(python_caller PRIVATE ${Python3_LIBRARIES})

set_target_properties(python_caller PROPERTIES COMPILE_FLAGS ${x64} LINK_FLAGS ${x64})
target_compile_options(python_caller PRIVATE -Wall -pedantic -O0) # g++ --help=warnings