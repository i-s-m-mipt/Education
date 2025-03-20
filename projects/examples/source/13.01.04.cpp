#include <ios>
#include <iostream>
#include <ostream>

/////////////////////////////////////////////////

int main()
{
    auto x = 1;

//  ---------------------------------------------

    std::cout << "main : x = " << x << '\n';

    std::cout << "main : x = " << x << std::endl;

//  ---------------------------------------------

    std::cout << "main : x = " << x << '\n';

    std::cout.flush();

//  ---------------------------------------------

    std::cout << std::unitbuf;

    std::cout << "main : x = " << x << '\n';
}