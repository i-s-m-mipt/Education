//////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  --------------------------------------------------------------

    std::cout << "main : enter int x : "; std::cin >> x;

//  --------------------------------------------------------------

    switch (auto y = x; y) // support : compiler-explorer.com
    {
        [[likely]] case 1 :
            
        [[likely]] case 2 :

    //  ----------------------------------------------------------

        [[likely]] case 3 :
        {
            std::cout << "main : selection (1)\n";
            
        //  --------------------------------------
            
            [[fallthrough]];
        }

    //  ----------------------------------------------------------

        case 4 : { std::cout << "main : selection (2)\n"; break; }

        case 5 : { std::cout << "main : selection (3)\n"; break; }

    //  ----------------------------------------------------------
        
        [[unlikely]] default :
        {
            std::cout << "main : selection (4)\n";

        //  --------------------------------------
            
            break;
        }
    }
}

//////////////////////////////////////////////////////////////////