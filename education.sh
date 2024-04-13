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
cp ../source/13.07.algorithm.erase.comment.test.txt .
cp ../../../libraries/library_v2/liblibrary_v2.so .
