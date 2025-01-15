#include <iostream>

///////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        std::cout << "main : enter int : "; int x; std::cin >> x;

        std::cout << "main : selection (1) : " << (x == 1 ? "(1)\n" : "(2)\n");
    }
    
//  ---------------------------------------------------------------------------

    {
        std::cout << "main : enter int : "; int x; std::cin >> x;

        std::cout << "main : selection (2) : ";

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

//  ---------------------------------------------------------------------------

    {
        std::cout << "main : enter int : "; int x; std::cin >> x;

        std::cout << "main : selection (3) : ";

        switch (auto y = x; y) // support: compiler-explorer.com
        {
            [[likely]] case 1:
            [[likely]] case 2:
            [[likely]] case 3:
            {
                std::cout << "(1) "; [[fallthrough]];
            }
            case 4:
            {
                std::cout << "(2)\n"; break;
            }
            case 5:
            {
                std::cout << "(3)\n"; break;
            }
            [[unlikely]] default:
            {
                std::cout << "(4)\n"; break;
            }
        }
    }
}