#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

//  ================================================================================================

inline void cleanup() // note: cleanup will be called at exit
{
    std::cerr << "cleanup: bad allocation\n";
}

inline void handler() // note: handler will be called at every bad allocation
{
    std::cerr << "handler: bad allocation\n";

    std::exit(-1); // note: consider std::abort()
}

//  ================================================================================================

int main()
{
    std::atexit         (cleanup); // note: set callback function for exit
    std::set_new_handler(handler); // note: set callback function for new

//  ================================================================================================

    try
    {
        while (true)
        {
            new const int[100'000'000]{}; // note: constructor can throw exceptions
        }
    }
    catch (const std::bad_alloc & exception) // good: modern approach
    {
        std::cerr << "message: " << exception.what() << '\n';
    }

//  ================================================================================================

    while (true)
    {
        if (const auto array = new (std::nothrow) const int[100'000'000]{}; !array)
        {
            std::cerr << "pointer: bad allocation\n";

            break;
        }
    }

	return 0;
}