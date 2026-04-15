////////////////////////////////////////////////////////

// chapter : Streams

////////////////////////////////////////////////////////

// section : Streams

////////////////////////////////////////////////////////

// content : Stream Synchronization
//
// content : C-Style Streams
//
// content : Streams stdin, stdout and stderr
//
// content : Function std::print
//
// content : Function std::ios_base::sync_with_stdio

////////////////////////////////////////////////////////

#include <cstdio>
#include <iostream>
#include <print>

////////////////////////////////////////////////////////

int main()
{
    std::cin.tie(nullptr);

//  ----------------------------------------------------

    auto x = 0;

//  ----------------------------------------------------

    std::cout << "main : enter int x : "; std::cin >> x;

//  ----------------------------------------------------

    std::cout << "main (1)\n"; std::print("main (2)\n");

    std::cout << "main (3)\n";

//  ----------------------------------------------------

    std::ios_base::sync_with_stdio(false);

//  ----------------------------------------------------

    std::cout << "main (4)\n"; std::print("main (5)\n");

    std::cout << "main (6)\n";
}

////////////////////////////////////////////////////////