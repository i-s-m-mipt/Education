///////////////////////////////////////////////

// chapter : Parallel Programming

///////////////////////////////////////////////

// content : Passing Arguments to Function main

///////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cstring>
#include <print>
#include <thread>

///////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////

int main(int argc, char * argv[])
{
    assert(argc == 2);

//  -------------------------------------------

    assert(std::strcmp(argv[0], "14.54") == 0);

//  -------------------------------------------

    auto string = argv[1];

//  -------------------------------------------

    std::print("main : string = {}\n", string);

//  -------------------------------------------

    std::this_thread::sleep_for(1s);

//  -------------------------------------------

    return 0;
}

///////////////////////////////////////////////