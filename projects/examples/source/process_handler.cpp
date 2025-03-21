#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals;

int main(int argc, char ** argv)
{
    assert(argc == 3);

    std::cout << argv[0] << ' ' << argv[1] << ' ' << argv[2] << '\n';

    std::this_thread::sleep_for(5s);
}