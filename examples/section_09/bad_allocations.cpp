#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

void cleanup() // note: cleanup will be called at exit
{
    std::cerr << "cleanup: bad allocation" << std::endl;
}

void handler() // note: handler will be called at every bad allocation
{
    std::cerr << "handler: bad allocation" << std::endl;

    std::exit(-1); // note: consider std::abort()
}

int main()
{
    std::atexit         (cleanup); // note: set callback function for exit
    std::set_new_handler(handler); // note: set callback function for new

    try
    {
        while (true)
        {
            new int[100'000'000]; // note: constructor can throw exceptions
        }
    }
    catch (const std::bad_alloc & exception) // good: modern approach
    {
        std::cerr << "message: " << exception.what() << std::endl;
    }

    while (true)
    {
        if (auto ptr = new(std::nothrow) int[100'000'000]; !ptr) // note: controversial decision
        {
            std::cerr << "pointer: bad allocation" << std::endl;

            break;
        }
    }

	return 0;
}