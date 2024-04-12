#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

int main(int argc, char ** argv)
{
    assert(argc == 3); // note: program name and 2 arguments

    std::cout << argv[0] << ' ' << 
                 argv[1] << ' ' << 
                 argv[2] << std::endl;

    std::this_thread::sleep_for(10s);

    return 0;
}