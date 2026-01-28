/////////////////////////////////////////////////////////////

// chapter : Basics of Programming

/////////////////////////////////////////////////////////////

// section : Selection Statements

/////////////////////////////////////////////////////////////

// content : Statement if
//
// content : Tool Compiler Explorer

/////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

/////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  ---------------------------------------------------------

    std::print("main : enter int x : "); std::cin >> x;

//  ---------------------------------------------------------

    if (auto y = x; y > 0) // support : compiler-explorer.com
    {
        std::print("main : selection (1)\n");
    }
    else if (0 == y)
    {
        std::print("main : selection (2)\n");
    }
    else
    {
        std::print("main : selection (3)\n");
    }
}

/////////////////////////////////////////////////////////////