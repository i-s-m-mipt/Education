###################################################################################################

# url="https://sourceforge.net/projects/boost/files/boost/1.85.0/boost_1_85_0.tar.gz/download"
#
# wget -O boost_1_85_0.tar.gz $url
#
# tar xvf boost_1_85_0.tar.gz
#
# cd boost_1_85_0/
#
# sudo apt update
#
# sudo apt install autotools-dev build-essential libboost-all-dev libbz2-dev libicu-dev python3-dev
#
# ./bootstrap.sh
#
# options="toolset=gcc variant=release link=static runtime-link=static threading=multi"
#
# sudo ./b2 $options -j8 install
#
# ./bootstrap.sh --with-python=python3
#
# sudo ./b2 --with-python $options -j8 install

###################################################################################################

mkdir -p libraries

###################################################################################################

cd projects/library_v1

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libstatic.a ../../../libraries && cd ../../../

###################################################################################################

cd projects/library_v2

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libshared.so ../../../libraries && cd ../../../

###################################################################################################

cd projects/examples

mkdir -p output && cd "$_"

cmake .. && cmake --build .

###################################################################################################

cp ../../../libraries/libshared.so .

cp ../source/{script.py,source.cpp,font.ttf,image.jpg} .

###################################################################################################

files="../source/06.01.07.cpp ../source/06.01.08.cpp"

g++ -c -std=c++23 -Wall -Wextra -pedantic -O0 ../source/06.01.06.hpp -o 06.01.06.hpp.gch

g++    -std=c++23 -Wall -Wextra -pedantic -O0 $files -ltbb -o 06.01.08

###################################################################################################

files="../source/06.02.04.cpp 06.02.01.o 06.02.02.o 06.02.03.o"

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 -xc++-system-header iostream

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.03.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.01.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.02.02.cxx

g++    -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 $files -o 06.02.04

###################################################################################################