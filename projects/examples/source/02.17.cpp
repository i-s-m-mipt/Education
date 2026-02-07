/////////////////////////////////////////////////////////////

// chapter : Basics of Programming

/////////////////////////////////////////////////////////////

// section : Operators and Expressions

/////////////////////////////////////////////////////////////

// content : Function std::print
//
// content : String Literals
//
// content : Null-Terminated Strings
//
// content : Stream std::cin
//
// content : Operator >>
//
// content : Selection Statements
//
// content : Statement if
//
// content : Scoped Variables
//
// content : Service Compiler Explorer

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