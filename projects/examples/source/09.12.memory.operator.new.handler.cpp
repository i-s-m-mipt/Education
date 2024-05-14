#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

//  ================================================================================================

inline void cleanup()
{
    std::cerr << "cleanup: bad allocation\n";
}

inline void handler()
{
    std::cerr << "handler: bad allocation\n";

    std::exit(-1); // suport: std::abort()
}

//  ================================================================================================

int main()
{
    std::atexit         (cleanup);
    std::set_new_handler(handler);

//  ================================================================================================

    try
    {
        while (true)
        {
            new const int[100'000'000]{};
        }
    }
    catch (const std::bad_alloc & exception)
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