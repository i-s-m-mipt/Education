/////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

/////////////////////////////////////////////////////////////////////////

// section : Dynamic Memory

/////////////////////////////////////////////////////////////////////////

// content : Dynamic Memory
//
// content : Handling Memory Errors
//
// content : Function std::set_new_handler
//
// content : Callback Functions
//
// content : Exception std::bad_alloc
//
// content : Object std::nothrow

/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <new>
#include <print>

/////////////////////////////////////////////////////////////////////////

void test() 
{ 
    std::print("test\n");

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
    catch (std::bad_alloc const & exception)
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

/////////////////////////////////////////////////////////////////////////