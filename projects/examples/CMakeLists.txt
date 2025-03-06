cmake_minimum_required(VERSION 3.28)

#####################################################################################################################

project(examples VERSION 24.02.06 LANGUAGES CXX)

#####################################################################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

#####################################################################################################################

set(Boost_USE_STATIC_LIBS ON)

set(Boost_USE_STATIC_RUNTIME ON)

# support: /usr/share/cmake/modules

#####################################################################################################################

find_package(Boost         1.85 REQUIRED COMPONENTS filesystem locale log python312 system timer unit_test_framework)
find_package(GTest         1.14 REQUIRED COMPONENTS)
find_package(benchmark          REQUIRED COMPONENTS)
find_package(Python        3.10 REQUIRED COMPONENTS Interpreter Development)
find_package(ICU                REQUIRED COMPONENTS i18n uc)
find_package(nlohmann_json 3.10 REQUIRED COMPONENTS)
find_package(PDFHummus          REQUIRED COMPONENTS)
find_package(TBB                REQUIRED COMPONENTS)

find_package(SFML               REQUIRED COMPONENTS graphics system window) # TODO

#####################################################################################################################

include_directories(        ${Boost_INCLUDE_DIRS})
include_directories(        ${GTEST_INCLUDE_DIRS})
include_directories(    ${benchmark_INCLUDE_DIRS})
include_directories(       ${Python_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(    ${PDFHummus_INCLUDE_DIRS})
include_directories(          ${TBB_INCLUDE_DIRS})
include_directories(${libwebsockets_INCLUDE_DIRS})
include_directories(         ${SFML_INCLUDE_DIRS})

#####################################################################################################################

set(debug

#   01.01.01
    01.02.01
    01.02.02
#   01.03.01
    02.01.01
    02.01.02
    02.01.03
    02.01.04
    02.01.05
    02.01.06
    02.01.07
    02.01.08
    02.01.09
    02.01.10
    02.02.01
    02.02.02
    02.02.03
    02.02.04
    02.02.05
    02.02.06
    02.02.07
    02.02.08
    02.02.09
    02.02.10
    02.02.11
    02.02.12
    02.02.13
    02.02.14
    02.02.15
    02.03.01
    02.03.02
    02.03.03
    02.03.04
    02.03.05
    02.03.06
    02.03.07
    02.03.08
    02.03.09
    02.03.10
    02.03.11
    02.03.12
    02.04.01
    02.04.02
    02.04.03
    02.04.04
    02.04.05
    02.04.06
    02.04.07
    03.01.01
    03.01.02
    03.01.03
    03.01.04
    03.01.05
    03.01.06
    03.01.07
    03.02.01
    03.02.02
    03.02.03
    03.02.04
    03.02.05
    03.02.06
    03.02.07
#   03.02.08
    03.02.09
    03.02.10
    03.02.11
#   03.02.12
    03.02.13
    03.02.14
    03.02.15
    03.02.16
    03.02.17
#   03.03.01
    03.03.02
    03.03.03
    03.03.04
    03.03.05
    03.03.06
    03.03.07
    03.04.01
    03.04.02
    03.04.03
    03.04.04
    03.04.05
    03.04.06
    03.04.07
    04.01.01
    04.01.02
    04.01.03
    04.01.04
    04.01.05
    04.01.06
    04.01.07
    04.02.01
    04.02.02
    04.02.03
    04.02.04
    04.02.05
    04.02.06
    04.02.07
    04.03.01
    04.03.02
    04.03.03
    04.03.04
    04.03.05
    04.03.06
    04.03.07
    04.03.08
    04.03.09
    04.03.10
    04.03.11
    04.03.12
    04.03.13
    04.03.14
    04.03.15
    04.03.16
    04.03.17
    04.03.18
    04.03.19
    04.03.20
    04.03.21
    04.03.22
    04.03.23
    04.03.24
    04.03.25
    04.03.26
    05.01.01
    05.01.02
    05.01.03
    05.01.04
    05.01.05
    05.01.06
    05.02.01
    05.02.02
    05.02.03
    05.02.04
    05.02.05
    05.03.01
    05.03.02
    05.03.03
    05.03.04
    05.03.05
    05.04.01
    05.04.02
    05.04.03
    05.04.04
    05.04.05
    05.04.06
    05.04.07
    05.04.08
#   06.01.01
    06.01.02
    06.01.03
    06.01.04
#   06.01.05
#   06.01.06
#   06.01.07
#   06.01.08
#   06.01.09
#   06.01.10
#   06.01.11
    06.01.12
#   06.02.01
#   06.02.02
#   06.02.03
#   06.02.04
#   06.03.01
#   06.03.02
#   06.03.03
#   06.03.04
    07.01.01
    07.01.02
    07.01.03
    07.01.04
    07.01.05
    07.01.06
    07.01.07
    07.01.08
    07.01.09
    07.02.01
    07.02.02
    07.02.03
#   07.03.01
    07.03.02
    07.03.03
#   07.03.04
    07.03.05
#   07.03.06
)

#################################################

foreach(entry IN LISTS debug)

    add_executable         (${entry} source/${entry}.cpp)

    target_link_libraries  (${entry} PRIVATE ${Boost_LIBRARIES})
    
    target_link_libraries  (${entry} PRIVATE TBB::tbb)

    target_compile_options (${entry} PRIVATE -Wall -Wextra -pedantic -O0)

endforeach()

###################################################################################

add_executable             (06.01.11 source/06.01.10.cpp source/06.01.11.cpp)

target_compile_options     (06.01.11 PRIVATE -Wall -Wextra -pedantic -O0)

###################################################################################

add_executable             (06.03.01 source/06.03.01.cpp)

target_compile_options     (06.03.01 PRIVATE -Wall -Wextra -pedantic -O0)

target_include_directories (06.03.01 PRIVATE ${CMAKE_SOURCE_DIR}/../library_v1/source/)

target_link_libraries      (06.03.01 PRIVATE ${CMAKE_SOURCE_DIR}/../../libraries/library_v1/libstatic.a)

target_link_libraries      (06.03.01 PRIVATE ${Boost_LIBRARIES})

###############################################################################################

add_executable             (07.03.01 source/07.03.01.cpp)

target_compile_options     (07.03.01 PRIVATE -Wall -Wextra -pedantic -O0 -ggdb)

###########################################################################################################

#  add_executable             (07.03.04 source/07.03.04.cpp)

#  target_compile_options     (07.03.04 PRIVATE -Wall -Wextra -pedantic -O0)

#  target_link_libraries      (07.03.04 PRIVATE )

#######################################################################################################

add_executable             (07.03.06 source/07.03.06.cpp)

target_compile_options     (07.03.06 PRIVATE -Wall -Wextra -pedantic -O0)

target_link_libraries      (07.03.06 PRIVATE GTest::gtest)

###################################################################################################

#add_executable             (08.10.embedding.python.caller source/08.10.embedding.python.caller.cpp)

#target_compile_options     (08.10.embedding.python.caller PRIVATE -Wall -Wextra -pedantic -O0)

#target_link_libraries      (08.10.embedding.python.caller PRIVATE ${Boost_LIBRARIES})

#target_link_libraries      (08.10.embedding.python.caller PRIVATE Python::Python)

###################################################################################################

#add_executable             (09.05.iterator.classification source/09.05.iterator.classification.cpp)

#target_compile_options     (09.05.iterator.classification PRIVATE -Wall -Wextra -pedantic -O0) 

#target_compile_definitions (09.05.iterator.classification PRIVATE _GLIBCXX_DEBUG)

#########################################################################################################

#add_executable             (12.05.locale.facet.utf.converter source/12.05.locale.facet.utf.converter.cpp)

#target_compile_options     (12.05.locale.facet.utf.converter PRIVATE -Wall -Wextra -pedantic -O0)

#target_link_libraries      (12.05.locale.facet.utf.converter PRIVATE ${Boost_LIBRARIES})

#target_link_libraries      (12.05.locale.facet.utf.converter PRIVATE ICU::i18n ICU::uc)

########################################################################################

#add_executable             (13.13.serialization.pdf source/13.13.serialization.pdf.cpp)

#target_compile_options     (13.13.serialization.pdf PRIVATE -Wall -Wextra -pedantic -O0)

#target_link_libraries      (13.13.serialization.pdf PRIVATE PDFHummus::PDFWriter)

#################################################################################

set(release

    07.03.07
)

########################################

foreach(entry IN LISTS release)

    add_executable         (${entry} source/${entry}.cpp)

    target_compile_options (${entry} PRIVATE -Wall -pedantic -Wextra -O3)

    target_link_libraries  (${entry} PRIVATE ${Boost_LIBRARIES})

    target_link_libraries  (${entry} PRIVATE benchmark::benchmark)

    target_link_libraries  (${entry} PRIVATE TBB::tbb)

    target_link_libraries  (${entry} PRIVATE /usr/lib/gcc/x86_64-linux-gnu/13/libatomic.a)

endforeach()