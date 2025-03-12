#include <cstdlib>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

/////////////////////////////////////////////////////////////////////////

void test() 
{ 
    std::cout << "test\n"; 
    
    std::set_new_handler(nullptr); 
}

/////////////////////////////////////////////////////////////////////////

int main()
{
    std::set_new_handler(test);

//  ---------------------------------------------------------------------

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

//  ---------------------------------------------------------------------

    while (true)
    {
        if (auto array = new (std::nothrow) int[1'000'000'000]{}; !array)
        {
            break;
        }
    }
}