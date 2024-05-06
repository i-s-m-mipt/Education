#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

int main(int argc, char ** argv)
{
    assert(argc == 3);

    std::cout << argv[0] << ' ';
    std::cout << argv[1] << ' ';
    std::cout << argv[2] << std::endl;

    std::this_thread::sleep_for(10s);

    return 0;
}