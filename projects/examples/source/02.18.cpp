////////////////////////////////////////////////////////////////////

// chapter : Basics of Programming

////////////////////////////////////////////////////////////////////

// section : Selection Statements

////////////////////////////////////////////////////////////////////

// content : Statement switch
//
// content : Labels case and default
//
// content : Statement break
//
// content : Attributes [[fallthrough]], [[likely]] and [[unlikely]]

////////////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  -------------------------------------------------------------

    std::print("main : enter int x : "); std::cin >> x;

//  -------------------------------------------------------------

    switch (auto y = x; y) // support : compiler-explorer.com
    {
        [[likely]] case 1 :
            
        [[likely]] case 2 :

    //  ---------------------------------------------------------

        [[likely]] case 3 :
        {
            std::print("main : selection (1)\n");
            
        //  -------------------------------------
            
            [[fallthrough]];
        }

    //  ---------------------------------------------------------

        case 4 : { std::print("main : selection (2)\n"); break; }

        case 5 : { std::print("main : selection (3)\n"); break; }

    //  ---------------------------------------------------------
        
        [[unlikely]] default :
        {
            std::print("main : selection (4)\n");

        //  -------------------------------------
            
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////