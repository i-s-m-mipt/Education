#include <iostream>

int main()
{
    std::cout << "Enter 1 integer : "; int x; std::cin >> x;

//  ------------------------------------------------------------------------------------------------

    std::cout << "Selection (1) : ";

    std::cout << (x == 1 ? "(1)" : "(2)");

    std::cout << '\n';

//  ------------------------------------------------------------------------------------------------

    std::cout << "Selection (2) : ";

    if (auto y = x; 1 == y) // support: compiler-explorer.com
    {
        std::cout << "(1)";
    }
    else if (y > 1)
    {
        std::cout << "(2)";
    }
    else
    {
        std::cout << "(3)";
    }

    std::cout << '\n';

//  ------------------------------------------------------------------------------------------------

    std::cout << "Selection (3) : ";

    switch (auto z = x; z) // support: compiler-explorer.com
    {
        [[likely]] case 1:
        [[likely]] case 2:
        [[likely]] case 3:
        {
            std::cout << "(1)" << ' '; [[fallthrough]];
        }
        case 4:
        {
            std::cout << "(2)"; break;
        }
        case 5:
        {
            std::cout << "(3)"; break;
        }
        [[unlikely]] default:
        {
            std::cout << "(4)"; break;
        }
    }

    std::cout << '\n';
}