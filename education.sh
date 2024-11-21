mkdir -p libraries/library_v1
mkdir -p libraries/library_v2

cd projects/library_v1
mkdir -p output
cd output
cmake ..
cmake --build .
cp liblibrary_v1.a ../../../libraries/library_v1

cd ../../../projects/library_v2
mkdir -p output
cd output
cmake ..
cmake --build .
cp liblibrary_v2.so ../../../libraries/library_v2

cd ../../../projects/examples
mkdir -p output
cd output
cmake ..
cmake --build .
cp ../source/script.py .
cp ../source/matthias.jpg .
cp ../source/consolas.ttf .
cp ../source/13.07.algorithm.erase.comment.source.txt .
cp ../../../libraries/library_v2/liblibrary_v2.so .

g++ -c -std=c++23              -Wall -Wextra -pedantic -O0 ../source/06.03.project.header.precompiled.hpp -o 06.03.project.header.precompiled.hpp.gch

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 -xc++-system-header iostream

g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.08.project.module.submodule.cxx
g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.06.project.module.cxx
g++ -c -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.07.project.module.source.cxx

g++    -std=c++23 -fmodules-ts -Wall -Wextra -pedantic -O0 ../source/06.04.project.source.cpp ../source/06.05.project.source.main.cpp 06.06.project.module.o 06.07.project.module.source.o 06.08.project.module.submodule.o -o 06.05.project
