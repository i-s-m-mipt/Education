///////////////////////////////////////////////////////

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <print>
#include <string>

///////////////////////////////////////////////////////

using namespace std::literals;

///////////////////////////////////////////////////////

int main()
{
    std::print("main : __FILE__ = {}\n", __FILE__);

    std::print("main : __LINE__ = {}\n", __LINE__);

	std::print("main : __DATE__ = {}\n", __DATE__);

	std::print("main : __TIME__ = {}\n", __TIME__);

//  ---------------------------------------------------

	assert(__func__ == "main"s);

//  ---------------------------------------------------

    auto x = 0; 

//  ---------------------------------------------------
    
    std::print("main : enter int x : "); std::cin >> x;

//  ---------------------------------------------------

    if (x > 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

///////////////////////////////////////////////////////