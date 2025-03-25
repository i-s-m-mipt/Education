#include <iostream>

/////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  ---------------------------------------------------------

    std::cout << "main : enter int x : "; std::cin >> x;

    std::cout << "main : selection ";

//  ---------------------------------------------------------

    switch (auto y = x; y) // support : compiler-explorer.com
    {
        [[likely]] case 1 :
            
        [[likely]] case 2 :

        [[likely]] case 3 :
        {
            std::cout << "(1) "; [[fallthrough]];
        }
        case 4 :
        {
            std::cout << "(2)\n"; break;
        }
        case 5 :
        {
            std::cout << "(3)\n"; break;
        }
        [[unlikely]] default :
        {
            std::cout << "(4)\n"; break;
        }
    }
}