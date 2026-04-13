///////////////////////////////////////////////////////

// chapter : Memory

///////////////////////////////////////////////////////

// section : Memory

///////////////////////////////////////////////////////

// content : Memory
//
// content : Virtual Addresses
//
// content : Kernel and User Spaces
//
// content : Stack, Heap, Data, BSS and Text Segments
//
// content : Memory Mappings
//
// content : Tools pgrep and pmap
//
// content : Page Table
//
// content : Physical Addresses

///////////////////////////////////////////////////////

// support : pmap -x $(pgrep 09.17)

///////////////////////////////////////////////////////

#include <iostream>
#include <print>

///////////////////////////////////////////////////////

int main() 
{
    auto const size = 1uz << 20;

//  ---------------------------------------------------

    [[maybe_unused]]        int array_1[size]{};

    [[maybe_unused]] static int array_2[size]{};

//  ---------------------------------------------------

	auto array_3 = new int[1 << 30]{};

//  ---------------------------------------------------

	std::print("main : enter char : "); std::cin.get();

//  ---------------------------------------------------

    delete[] array_3;
}

///////////////////////////////////////////////////////