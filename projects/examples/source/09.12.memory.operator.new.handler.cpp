#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

//  ================================================================================================

void test_v1() { std::cerr << "test_v1\n"; }

void test_v2() { std::cerr << "test_v2\n"; std::exit(-1); }

//  ================================================================================================

int main()
{
    std::atexit(test_v1);
    
    std::set_new_handler(test_v2);

//  ================================================================================================

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

//  ================================================================================================

    while (true)
    {
        if (auto array = new (std::nothrow) int[1'000'000'000]{}; !array)
        {
            std::cerr << "main : bad allocation\n";

            break;
        }
    }
}