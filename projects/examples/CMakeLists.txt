#############################################################################################

cmake_minimum_required(VERSION 3.28)

#############################################################################################

project(examples VERSION 24.02.06 LANGUAGES CXX)

#############################################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

#############################################################################################

set(Boost_USE_STATIC_LIBS    ON)

set(Boost_USE_STATIC_RUNTIME ON)

#############################################################################################

find_package(Boost 1.85 REQUIRED COMPONENTS 

    filesystem 
    locale 
    log 
    python312 
    system 
    timer 
    unit_test_framework
)

#############################################################################################

find_package(glog          REQUIRED COMPONENTS)
find_package(GTest         REQUIRED COMPONENTS)
find_package(benchmark     REQUIRED COMPONENTS)
find_package(Python        REQUIRED COMPONENTS Interpreter Development)
find_package(ICU           REQUIRED COMPONENTS i18n uc)
find_package(nlohmann_json REQUIRED COMPONENTS)
find_package(PDFHummus     REQUIRED COMPONENTS)
find_package(zipper        REQUIRED COMPONENTS)
find_package(libpqxx       REQUIRED COMPONENTS)
find_package(TBB           REQUIRED COMPONENTS)

#############################################################################################

include_directories(        ${Boost_INCLUDE_DIRS})
include_directories(         ${glog_INCLUDE_DIRS})
include_directories(        ${GTEST_INCLUDE_DIRS})
include_directories(    ${benchmark_INCLUDE_DIRS})
include_directories(       ${Python_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(    ${PDFHummus_INCLUDE_DIRS})
include_directories(       ${zipper_INCLUDE_DIRS})
include_directories(      ${libpqxx_INCLUDE_DIRS})
include_directories(          ${TBB_INCLUDE_DIRS})

#############################################################################################

set(debug

    01.02
    01.04
    02.01
    02.02
    02.03
    02.04
    02.05
    02.06
    02.07
    02.08
    02.09
    02.10
    02.11
    02.12
    02.13
    02.14
    02.15
    02.16
    02.17
    02.18
    02.19
    02.20
    02.21
    02.22
    02.23
    02.24
    02.25
    02.26
    02.27
    02.28
    02.29
    02.30
    02.31
    02.32
    02.33
    02.34
    02.35
    02.36
    02.38
    02.39
    02.40
    02.41
    02.42
    02.43
    02.44
    02.45
    03.01
    03.02
    03.03
    03.04
    03.05
    03.06
    03.07
    03.08
    03.09
    03.10
    03.11
    03.12
    03.13
    03.15
    03.16
    03.17
    03.18
    03.20
    03.21
    03.22
    03.23
    03.24
    03.26
    03.27
    03.28
    03.29
    03.30
    03.31
    03.32
    03.33
    03.34
    03.35
    03.36
    03.37
    03.38
    04.01
    04.02
    04.03
    04.04
    04.05
    04.06
    04.07
    04.08
    04.09
    04.10
    04.11
    04.12
    04.13
    04.14
    04.15
    04.16
    04.17
    04.18
    04.19
    04.20
    04.21
    04.22
    04.23
    04.24
    04.25
    04.26
    04.27
    04.28
    04.29
    04.30
    04.31
    04.32
    04.33
    04.34
    04.35
    04.36
    04.37
    04.38
    04.39
    05.01
    05.02
    05.03
    05.04
    05.05
    05.06
    05.07
    05.08
    05.09
    05.10
    05.11
    05.12
    05.13
    05.14
    05.15
    05.16
    05.17
    05.18
    05.19
    05.20
    05.21
    05.22
    05.23
    05.24
    06.02
    06.03
    06.04
    06.12
    07.01
    07.02
    07.03
    07.04
    07.05
    07.06
    07.07
    07.08
    07.09
    07.10
    07.11
    07.12
    07.13
    07.17
    07.18
    07.19
    07.21
    08.01
    08.02
    08.03
    08.05
    08.07
    08.08
    08.10
    08.11
    08.12
    08.15
    08.16
    08.17
    08.18
    08.21
    08.22
    08.23
    08.24
    08.25
    08.26
    08.27
    08.28
    08.34
    08.35
    08.36
    08.39
    08.40
    08.41
    09.01
    09.02
    09.03
    09.04
    09.05
    09.06
    09.07
    09.08
    09.09
    09.10
    09.11
    09.12
    09.13
    09.15
    09.16
    09.18
    09.20
    09.21
    09.22
    09.23
    09.25
    09.26
    09.27
    09.37
    09.38
    09.39
    10.01
    10.02
    10.03
    10.04
    10.05
    10.06
    10.07
    10.08
    10.09
    10.10
    10.11
    10.13
    10.14
    10.15
    10.16
    10.17
    10.18
    10.19
    10.20
    10.22
    10.23
    10.24
    10.25
    10.26
    10.27
    10.28
    10.29
    10.30
    10.31
    10.32
    10.34
    10.37
    10.40
    10.41
    10.43
    10.44
    10.46
    10.47
    10.48
    10.49
    11.01
    11.02
    11.03
    11.04
    11.05
    11.06
    11.07
    11.08
    11.09
    11.10
    11.11
    11.12
    11.13
    11.14
    11.15
    11.16
    11.17
    11.18
    11.19
    11.20
    11.21
    11.22
    11.23
    11.24
    11.25
    11.26
    11.27
    11.28
    11.30
    11.31
    11.32
    12.02
    12.03
    12.04
    12.06
    12.07
    12.08
    12.09
    12.10
    12.11
    12.13
    12.15
    12.16
    12.17
    12.18
    12.19
    12.20
    12.22
    12.23
    12.24
    12.25
    12.26
    12.27
    12.28
    12.29
    13.02
    13.03
    13.04
    13.05
    13.06
    13.07
    13.08
    13.09
    13.10
    13.11
    13.12
    13.13
    13.14
    13.15
    13.16
    13.17
    13.18
    13.19
    14.02
    14.03
    14.04
    14.05
    14.06
    14.07
    14.08
    14.09
    14.10
    14.11
    14.12
    14.13
    14.15
    14.16
    14.17
    14.18
    14.19
    14.20
    14.21
    14.22
    14.23
    14.24
    14.25
    14.26
    14.27
    14.28
    14.30
    14.31
    14.33
    14.34
    14.36
    14.37
)

#############################################################################################

foreach(entry IN LISTS debug)

    add_executable         (${entry} source/${entry}.cpp)

    target_compile_options (${entry} PRIVATE -Wall -Wextra -Wpedantic -O0)

    target_link_libraries  (${entry} PRIVATE ${Boost_LIBRARIES})

    target_link_libraries  (${entry} PRIVATE TBB::tbb)

endforeach()

#############################################################################################

add_executable             (02.37 source/02.37.cpp)

target_compile_options     (02.37 PRIVATE -Wall -Wextra -Wpedantic -O0 -m32)

target_link_options        (02.37 PRIVATE -m32)

#############################################################################################

add_executable             (06.11 source/06.10.cpp source/06.11.cpp)

target_compile_options     (06.11 PRIVATE -Wall -Wextra -Wpedantic -O0)

#############################################################################################

add_executable             (06.17 source/06.17.cpp)

target_include_directories (06.17 PRIVATE ${CMAKE_SOURCE_DIR}/../library_v1/source/)

target_compile_options     (06.17 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (06.17 PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/libstatic.a)

target_link_libraries      (06.17 PRIVATE ${Boost_LIBRARIES})

#############################################################################################

add_executable             (07.14 source/07.14.cpp)

target_compile_options     (07.14 PRIVATE -Wall -Wextra -Wpedantic -O0 -g)

target_link_libraries      (07.14 PRIVATE -lstdc++exp)

#############################################################################################

add_executable             (07.15 source/07.15.cpp)

target_compile_options     (07.15 PRIVATE -Wall -Wextra -Wpedantic -O0 -ggdb)

#############################################################################################

add_executable             (07.16 source/07.16.cpp)

target_compile_options     (07.16 PRIVATE -Wall -Wextra -Wpedantic -O0 -g -fsanitize=address)

target_link_options        (07.16 PRIVATE -fsanitize=address)

#############################################################################################

add_executable             (07.20 source/07.20.cpp)

target_compile_options     (07.20 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (07.20 glog::glog)

#############################################################################################

add_executable             (07.22 source/07.22.cpp)

target_compile_options     (07.22 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (07.22 PRIVATE GTest::gtest)

#############################################################################################

add_executable             (08.20 source/08.20.cpp)

target_compile_options     (08.20 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (08.20 PRIVATE ${Boost_LIBRARIES})

target_link_libraries      (08.20 PRIVATE Python::Python)

#############################################################################################

add_executable             (09.14 source/09.14.cpp)

target_compile_options     (09.14 PRIVATE -Wall -Wextra -Wpedantic -O0) 

target_compile_definitions (09.14 PRIVATE _GLIBCXX_DEBUG)

#############################################################################################

add_executable             (12.05 source/12.05.cpp)

target_compile_options     (12.05 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (12.05 PRIVATE ${Boost_LIBRARIES})

target_link_libraries      (12.05 PRIVATE ICU::i18n ICU::uc)

#############################################################################################

add_executable             (13.20 source/13.20.cpp)

target_compile_options     (13.20 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (13.20 PRIVATE PDFHummus::PDFWriter)

#############################################################################################

add_executable             (13.21 source/13.21.cpp)

target_compile_options     (13.21 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (13.21 PRIVATE zipper::zipper)

#############################################################################################

add_executable             (13.22 source/13.22.cpp)

target_compile_options     (13.22 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries      (13.22 PRIVATE libpqxx::pqxx)

#############################################################################################

set(release

    07.23
    08.06
    08.09
    08.30
    08.32
    08.33
    08.37
    08.38
    09.19
    09.24
    09.29
    09.31
    09.33
    09.35
    09.36
    09.40
    10.12
    10.33
    10.35
    10.38
    10.39
    12.12
    14.14
    14.32
    14.35
)

#############################################################################################

foreach(entry IN LISTS release)

    add_executable         (${entry} source/${entry}.cpp)

    target_compile_options (${entry} PRIVATE -Wall -Wpedantic -Wextra -O3)

    target_link_libraries  (${entry} PRIVATE ${Boost_LIBRARIES})

    target_link_libraries  (${entry} PRIVATE benchmark::benchmark)

    target_link_libraries  (${entry} PRIVATE TBB::tbb)

endforeach()

#############################################################################################

add_executable             (10.45 source/10.45.cpp)

target_compile_options     (10.45 PRIVATE -Wall -Wextra -Wpedantic -O3)

target_link_libraries      (10.45 PRIVATE ${Boost_LIBRARIES})

target_link_libraries      (10.45 PRIVATE Python::Python)

#############################################################################################

add_executable             (14.29 source/14.29.cpp)

target_compile_options     (14.29 PRIVATE -Wall -Wextra -Wpedantic -O3)

target_link_libraries      (14.29 PRIVATE TBB::tbb)

target_link_libraries      (14.29 PRIVATE /usr/lib/gcc/x86_64-linux-gnu/13/libatomic.a)

#############################################################################################