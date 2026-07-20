/////////////////////////////////////////////////////////////////////

// chapter : Language Core Basics

/////////////////////////////////////////////////////////////////////

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
// content : Structured Programming
//
// content : Statement if
//
// content : Scoped Variables
//
// content : Assembly Language Representation
//
// content : Service Compiler Explorer
//
// content : Options -S, -masm=intel and -masm=att

/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

/////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  -----------------------------------------------------------------

    std::print("main : enter int x : "); std::cin >> x;

//  -----------------------------------------------------------------

    if (auto y = x; y > 0) // support : https://compiler-explorer.com
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

/////////////////////////////////////////////////////////////////////