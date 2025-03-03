#include <iostream>

//////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "main : enter int : "; auto x = 0; std::cin >> x;

    std::cout << "main : selection : ";

//  --------------------------------------------------------------
    
    std::cout << (x == 1 ? "(1)\n" : "(2)\n");
}