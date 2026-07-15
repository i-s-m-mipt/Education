///////////////////////////////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////////////////////////////

// content : Virtual and Physical Memory
//
// content : Memory Segments
//
// content : Stack, Heap, Data, Block Started by Symbol (BSS) and Text Segments
//
// content : Memory Mappings
//
// content : Tools pgrep and pmap
//
// content : Memory Management Unit (MMU)

///////////////////////////////////////////////////////////////////////////////

// support : pmap -x $(pgrep 09.18)

///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <print>

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////