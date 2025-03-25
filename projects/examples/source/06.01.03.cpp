#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

//////////////////////////////////////////////////////////

int main()
{
    std::cout << "main : __FILE__ = " << __FILE__ << '\n';

    std::cout << "main : __LINE__ = " << __LINE__ << '\n';

	std::cout << "main : __DATE__ = " << __DATE__ << '\n';

	std::cout << "main : __TIME__ = " << __TIME__ << '\n';

//  ------------------------------------------------------

	assert(__func__ == "main"s);

//  ------------------------------------------------------

    auto x = 0; 

//  ------------------------------------------------------
    
    std::cout << "main : enter int x : "; std::cin >> x;

//  ------------------------------------------------------

    if (x > 0)
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}