#include <iostream>

//////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "main : enter int : "; auto x = 0; std::cin >> x;

    std::cout << "main : selection : ";

//  --------------------------------------------------------------

    if (auto y = x; 1 == y) // support: compiler-explorer.com
    {
        std::cout << "(1)\n";
    }
    else if (y > 1)
    {
        std::cout << "(2)\n";
    }
    else
    {
        std::cout << "(3)\n";
    }
}