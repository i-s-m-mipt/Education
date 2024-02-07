cmake_minimum_required(VERSION 3.27.4)

project(examples VERSION 24.02.06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(x32 -m32)
set(x64 -m64)

find_package(Boost) # sudo apt-get install libboost-all-dev

include_directories(${Boost_INCLUDE_DIRS})

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