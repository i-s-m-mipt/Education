#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

//  ================================================================================================

void handler_v1() { std::cout << "handler_v1\n"; std::set_new_handler(nullptr); }

void handler_v2() { std::cout << "handler_v2\n"; }

//  ================================================================================================

int main()
{
    std::set_new_handler(handler_v1);

    try
    {
        while (true) 
        {
            new int[1'000'000'000]{};
        }
    }
    catch (const std::bad_alloc & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  -------------------------------------------------------

    std::atexit(handler_v2);

    while (true)
    {
        if (auto array = new (std::nothrow) int[1'000'000'000]{}; !array)
        {
            std::exit(-1);
        }
    }
}