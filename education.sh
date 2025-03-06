mkdir -p libraries/library_v1 && cd projects/library_v1

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libstatic.a ../../../libraries/library_v1 && cd ../../../

##############################################################################################################################

mkdir -p libraries/library_v2 && cd projects/library_v2

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libshared.so ../../../libraries/library_v2 && cd ../../../

##############################################################################################################################

cd projects/examples

mkdir -p output && cd "$_"

cmake .. && cmake --build .

##############################################################################################################################

cp ../../../libraries/library_v2/libshared.so .

##############################################################################################################################

g++ -c -std=c++23              -Wall -Wextra -pedantic -O0 ../source/06.01.06.hpp -o 06.01.06.hpp.gch

g++    -std=c++23              -Wall -Wextra -pedantic -O0 ../source/06.01.07.cpp ../source/06.01.08.cpp -o 06.01.08

##############################################################################################################################

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 -xc++-system-header iostream

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.03.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.01.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.02.cxx

g++    -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.04.cpp 06.02.01.o 06.02.02.o 06.02.03.o -o 06.02.04