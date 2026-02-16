##############################################################################################

# sudo snap refresh && sudo snap install --classic code
#
# sudo apt update && sudo apt upgrade -y
#
# sudo add-apt-repository ppa:ubuntu-toolchain-r/test
#
# sudo apt update
#
# sudo apt install g++-14
#
# sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100
#
# sudo apt install git cmake gdb valgrind kcachegrind linux-tools-common linux-tools-generic
#
# sudo apt install python3 python3-dev libicu-dev libtbb-dev

##############################################################################################

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
# sudo apt install autotools-dev build-essential libboost-all-dev libbz2-dev
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

##############################################################################################

# git clone https://github.com/google/glog
#
# cd glog
#
# mkdir -p output && cd "$_"
#
# cmake .. && cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# git clone https://github.com/google/googletest
#
# cd googletest
#
# mkdir -p output && cd "$_"
#
# cmake .. && cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# git clone https://github.com/google/benchmark
#
# cd benchmark
#
# mkdir -p output && cd "$_"
#
# cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ..
#
# cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# git clone https://github.com/nlohmann/json
#
# cd json
#
# mkdir -p output && cd "$_"
#
# cmake .. && cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# git clone https://github.com/galkahana/PDF-Writer
#
# cd PDF-Writer
#
# mkdir -p output && cd "$_"
#
# cmake .. && cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# git clone https://github.com/lecrapouille/zipper --recursive
#
# cd zipper
#
# mkdir -p output && cd "$_"
#
# sudo apt-get install zlib1g-dev
#
# cmake .. -DZIPPER_SHARED_LIB=ON -DZIPPER_BUILD_DEMOS=ON -DZIPPER_BUILD_TESTS=ON
#
# cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

# sudo apt update
#
# sudo apt install postgresql postgresql-contrib
#
# sudo apt-get install libpq-dev
#
# git clone https://github.com/jtv/libpqxx
#
# cd libpqxx
#
# mkdir -p output && cd "$_"
#
# cmake .. && cmake --build . --config Release
#
# sudo cmake --install .

##############################################################################################

mkdir -p libraries

##############################################################################################

cd projects/library_v1

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libstatic.a ../../../libraries && cd ../../../

##############################################################################################

cd projects/library_v2

mkdir -p output && cd "$_"

cmake .. && cmake --build .

cp libshared.so ../../../libraries && cd ../../../

##############################################################################################

cd projects/examples

mkdir -p output && cd "$_"

cmake .. && cmake --build .

##############################################################################################

cp ../../../libraries/libshared.so .

cp ../source/{font.ttf,image.jpg,script.py,source.cpp} .

##############################################################################################

files="../source/06.07.cpp ../source/06.08.cpp"

g++ -c -std=c++23 -Wall -Wextra -Wpedantic -O0 ../source/06.06.hpp -o ../source/06.06.hpp.gch

g++    -std=c++23 -Wall -Wextra -Wpedantic -O0 $files -ltbb -o 06.08

rm ../source/06.06.hpp.gch

##############################################################################################

files="../source/06.16.cpp 06.13.o 06.14.o 06.15.o"

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 -xc++-system-header print

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.15.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.13.cxx

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 ../source/06.14.cxx

g++    -std=c++23 -fmodules-ts -Wall -Wextra -Wpedantic -O0 $files -o 06.16

##############################################################################################