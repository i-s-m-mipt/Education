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

set(section_01 source/section_01/)

set(sources_01 
    minimal_program
    standard_library)

foreach(entry IN LISTS sources_01)
    add_executable        (${entry} ${section_01}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_02 source/section_02/)

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
    add_executable        (${entry} ${section_02}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_03 source/section_03/)

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
    virtual_functions
    virtual_operators)

foreach(entry IN LISTS sources_03)
    add_executable        (${entry} ${section_03}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_04 source/section_04/)

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
    add_executable        (${entry} ${section_04}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_05 source/section_05/)

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
    add_executable        (${entry} ${section_05}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_06 source/section_06/)

set(sources_06
    types_inference
    custom_typelist
    perfect_forward
    sfinae_enable_if)

foreach(entry IN LISTS sources_06)
    add_executable        (${entry} ${section_06}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
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

set(section_12 source/section_12/)

set(sources_12
    advanced_visitors
    algorithms_on_graphs
    algorithms_on_ranges
    function_objects
    function_pointers
    heterogeneous_vector
    insert_iterators
    lambda_expressions
    pattern_command
    pattern_visitor
    standard_algorithms
    depth_first_search
    breadth_first_search
    dijkstra_algorithm)

foreach(entry IN LISTS sources_12)
    add_executable        (${entry} ${section_12}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

set(section_13 source/section_13/)

set(sources_13
    recursive_calculator
    boost_spirit_basics
    parser_for_complex
    parser_for_romans
    parser_for_structs
    advanced_calculator
    character_variants
    locales_and_facets
    formatting_library
    regular_expressions)

foreach(entry IN LISTS sources_13)
    add_executable        (${entry} ${section_13}${entry}.cpp)
    set_target_properties (${entry} PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
    target_compile_options(${entry} PRIVATE -Wall -pedantic -O0) 
endforeach()

add_executable        (convert_encodings ${section_13}convert_encodings.cpp)
target_link_libraries (convert_encodings PRIVATE ${Boost_LIBRARIES})
set_target_properties (convert_encodings PROPERTIES COMPILE_FLAGS -m64 LINK_FLAGS -m64)
target_compile_options(convert_encodings PRIVATE -Wall -pedantic -O0)

set(sources_13_release
    strings_string_views)

foreach(entry IN LISTS sources_13_release)
    add_executable        (${entry} ${section_13}${entry}.cpp)
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