cd projects/library_v1
mkdir -p output
cd output
cmake ..
cmake --build .

cd ../../../projects/library_v2
mkdir -p output
cd output
cmake ..
cmake --build .

cd ../../../projects/examples
mkdir -p output
cd output
cmake ..
cmake --build .