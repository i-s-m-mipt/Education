cmake_minimum_required(VERSION 3.27)

# =======================================================================================================================

project(examples VERSION 24.02.06 LANGUAGES CXX)

# =======================================================================================================================

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# =======================================================================================================================

find_package(Boost         1.84 REQUIRED COMPONENTS filesystem locale log python system timer unit_test_framework)
find_package(Python3       3.11 REQUIRED COMPONENTS Interpreter Development)
find_package(nlohmann_json 3.11 REQUIRED COMPONENTS)
find_package(GTest         1.14 REQUIRED COMPONENTS)
find_package(benchmark          REQUIRED COMPONENTS)
find_package(PDFHummus          REQUIRED COMPONENTS)
find_package(TBB                REQUIRED COMPONENTS tbb)
find_package(SFML               REQUIRED COMPONENTS graphics system window)

# =======================================================================================================================

include_directories(        ${Boost_INCLUDE_DIRS})
include_directories(      ${Python3_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(        ${GTEST_INCLUDE_DIRS})
include_directories(    ${benchmark_INCLUDE_DIRS})
include_directories(    ${PDFHummus_INCLUDE_DIRS})
include_directories(          ${TBB_INCLUDE_DIRS})
include_directories(         ${SFML_INCLUDE_DIRS})

# ======================================================================================================================

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
    02.12.algorithm.recursive.sequence
    02.13.algorithm.insertion.merge.sorting
    03.01.class.struct
    03.02.class
    03.03.class.friend
    03.04.pattern.attorney.client.passkey
    03.05.class.relationship
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
    03.16.implementation.container.vector
    03.17.class.operator.overload
    03.18.class.operator.overload.output
    03.19.class.operator.overload.spaceship
    03.20.class.operator.overload.optimization
    04.01.template.function
    04.02.template.function.variadic
    04.03.template.function.variadic.tree.traversal
    04.04.template.class
    04.05.template.class.friend
    04.06.template.alias.variable
    04.07.template.metaprogramming
    04.08.template.metaprogramming.constexpr
    04.09.template.metaprogramming.constexpr.hybrid
    04.10.reference.lvalue.rvalue.forwarding
    04.11.template.type.inference
    04.12.pattern.sfinae
    04.13.implementation.template.type.trait
    04.14.implementation.template.type.concept
    04.15.implementation.utility.tlist
    04.16.implementation.utility.tuple
    04.17.utility.tuple
    05.01.pattern.builder
    05.02.pattern.factory
    05.03.pattern.prototype
    05.04.pattern.singleton
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
    05.15.pattern.mixin.crtp
    05.16.pattern.mixin.singleton
    05.17.pattern.mixin.barton.nackman
    05.18.pattern.mixin.invertion
    05.19.pattern.mixin.initialization
    05.20.pattern.mixin.inheritance.variadic
#   06.01.project.translation
#   06.02.project.header
#   06.03.project.header.precompiled
#   06.04.project.source
#   06.05.project.source.main
#   06.06.project.module
#   06.07.project.module.source
#   06.08.project.module.submodule
#   06.09.project.tool.cmake
#   06.10.project.library.static
#   06.11.project.library.shared
    07.01.error.assertion.termination
    07.02.class.union
    07.03.utility.variant.optional
    07.04.error.exception
    07.05.error.exception.stack.interface
    07.06.project.tool.boost.logging
    07.07.project.tool.boost.testing
    07.09.project.tool.profiler.cpu
    07.10.project.tool.profiler.memory
    07.12.project.tool.google.testing
    08.02.algorithm.binary.gray.code
    08.03.algorithm.indian.exponentiation
    08.04.class.enumeration
    08.05.number.floating
    08.06.number.complex
    08.07.number.integral.multiprecision
    08.08.number.floating.multiprecision
    08.09.implementation.class.big.int
    08.10.embedding.python.caller
#   08.11.embedding.python.script
#   08.13.algorithm.monte.carlo
    08.15.time.chrono
    08.16.time.chrono.calendar
    08.17.implementation.operator.literal
    09.01.pointer.smart
    09.02.pointer.smart.shared.this
    09.03.implementation.pointer.smart.unique
    09.04.implementation.pointer.smart.shared
    09.06.implementation.iterator.forward.list
    09.07.implementation.iterator.forward.list.facade
    09.08.pattern.facade
#   09.09.memory.address.space
#   09.10.memory.address.translation
    09.12.memory.operator.new.handler
    09.14.implementation.utility.optional
    09.15.memory.allocator.standard
#   09.16.memory.allocator
#   09.17.memory.allocator.block
    09.23.implementation.allocator.arena.adaptor
#   10.01.container.vector.deque.array.list.memory
    10.02.container.vector.deque.array.list
    10.04.pattern.proxy.vector
    10.05.container.multidimensional
    10.06.container.multidimensional.multiarray
    10.08.container.multidimensional.valarray
    10.09.algorithm.longest.common.subsequence
    10.10.container.adaptor
    10.11.container.adaptor.stack
#   10.12.container.circular.buffer.memory
    10.13.container.circular.buffer
#   10.14.container.red.black.tree.memory
    10.16.implementation.function.hash
#   10.17.container.hash.table.memory
    10.18.container.hash.table
    10.19.implementation.class.functor.hash.equal
    10.20.container.multiindex.bimap
    10.21.pattern.flyweight
    11.01.pointer.function
    11.02.class.functor
    11.03.class.functor.lambda.expression
    11.04.pattern.command
    11.05.pattern.visitor
    11.06.pattern.visitor.utility.variant
    11.07.pattern.visitor.utility.any
    11.08.implementation.utility.variant
    11.09.template.metaprogramming.cartesian.product
    11.10.algorithm.iterator.adaptor.inserter
    11.11.algorithm.standard
    11.12.algorithm.standard.range.view
    11.13.algorithm.graph
#   11.14.algorithm.graph.example
    11.15.algorithm.graph.traversal.bfs
    11.16.algorithm.graph.traversal.dfs
    11.17.algorithm.graph.search.dijkstra
    12.01.character.encoding
#   12.02.character.encoding.unicode.utf
    12.04.locale.facet
    12.05.locale.facet.utf.converter
#   12.06.parser.regex.ecma.script
    12.07.parser.regex
#   12.08.parser.grammar.arithmetic
    12.09.parser.grammar.arithmetic.calculator
    12.10.parser.spirit.number.integer
    12.11.parser.spirit.number.complex
    12.12.parser.spirit.number.romanus
    12.13.parser.spirit.fusion.class.structure
    12.14.parser.spirit.grammar.arithmetic.calculator
#   13.01.stream.class.inheritance
    13.02.stream.class
    13.03.stream.class.file
    13.04.stream.class.string
    13.05.stream.iterator.buffer.input.output
    13.06.algorithm.erase.comment
#   13.07.algorithm.erase.comment.source
    13.08.stream.output.format
    13.09.filesystem.path
    13.10.filesystem.directory
    13.11.filesystem.directory.iterator
    13.12.serialization.json
    13.13.serialization.pdf
#   14.01.concurrency.process.thread
    14.02.concurrency.thread
    14.03.concurrency.thread.reduce
    14.04.concurrency.thread.reduce.async
    14.05.concurrency.thread.reduce.packaged.task
)

# =======================================================================================================================

foreach(entry IN LISTS debug)

    add_executable         (${entry} source/${entry}.cpp)

    target_link_libraries  (${entry} PRIVATE      ${Boost_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE    ${Python3_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE ${GTEST_BOTH_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE    PDFHummus::PDFWriter)
    target_link_libraries  (${entry} PRIVATE                     tbb)

    target_compile_options (${entry} PRIVATE -Wall -Wextra -pedantic -O0)

endforeach()

# =======================================================================================================================

add_executable             (06.12.project.library source/06.12.project.library.cpp)

target_include_directories (06.12.project.library PRIVATE ${CMAKE_SOURCE_DIR}/../library_v1/source/)

target_link_libraries      (06.12.project.library PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/library_v1/liblibrary_v1.a)

target_link_libraries      (06.12.project.library PRIVATE ${Boost_LIBRARIES})

target_compile_options     (06.12.project.library PRIVATE -Wall -Wextra -pedantic -O0)

# =======================================================================================================================

add_executable             (07.08.project.tool.debugger source/07.08.project.tool.debugger.cpp)

target_compile_options     (07.08.project.tool.debugger PRIVATE -Wall -Wextra -pedantic -O0 -ggdb)

# =======================================================================================================================

add_executable             (09.05.iterator.classification source/09.05.iterator.classification.cpp)

target_compile_options     (09.05.iterator.classification PRIVATE -Wall -Wextra -pedantic -O0) 

target_compile_definitions (09.05.iterator.classification PRIVATE _GLIBCXX_DEBUG)

# =======================================================================================================================

set(release

    07.11.project.tool.google.benchmark
    08.01.number.integral
    08.12.number.random.generation
    08.14.algorithm.monte.carlo.simplex
    09.11.memory.alignment
    09.13.memory.operator.new.placement
    09.18.implementation.allocator.arena
    09.19.implementation.allocator.stack
    09.20.implementation.allocator.chain
    09.21.implementation.allocator.block
    09.22.implementation.allocator.fixed
    09.24.memory.allocator.polymorphism
    10.03.container.vector.deque.array.list.sorting
    10.07.container.multidimensional.ublas
    10.15.container.red.black.tree
    12.03.character.string.view
    14.06.concurrency.algorithm.standard
)

# =======================================================================================================================

foreach(entry IN LISTS release)

    add_executable         (${entry} source/${entry}.cpp)

    target_link_libraries  (${entry} PRIVATE      ${Boost_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE    ${Python3_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE ${GTEST_BOTH_LIBRARIES})
    target_link_libraries  (${entry} PRIVATE    benchmark::benchmark)
    target_link_libraries  (${entry} PRIVATE    PDFHummus::PDFWriter)
    target_link_libraries  (${entry} PRIVATE                     tbb)

    target_compile_options (${entry} PRIVATE -Wall -pedantic -Wextra -O3)

endforeach()

# =======================================================================================================================

add_executable         (17.01.multimedia.modeling.physics source/17.01.multimedia.modeling.physics/main.cpp
                                                          source/17.01.multimedia.modeling.physics/system.cpp
                                                          source/17.01.multimedia.modeling.physics/particle.cpp
                                                          source/17.01.multimedia.modeling.physics/link.cpp 
                                                          source/17.01.multimedia.modeling.physics/pressure.cpp)

target_link_libraries  (17.01.multimedia.modeling.physics PRIVATE sfml-graphics sfml-system sfml-window)

target_compile_options (17.01.multimedia.modeling.physics PRIVATE -Wall -Wextra -pedantic -O3)

# =======================================================================================================================

add_executable         (17.02.multimedia.modeling.fractal source/17.02.multimedia.modeling.fractal/main.cpp
                                                          source/17.02.multimedia.modeling.fractal/calculator.cpp
                                                          source/17.02.multimedia.modeling.fractal/visualizer.cpp)

target_link_libraries  (17.02.multimedia.modeling.fractal PRIVATE sfml-graphics sfml-system sfml-window)

target_compile_options (17.02.multimedia.modeling.fractal PRIVATE -Wall -Wextra -pedantic -O3)