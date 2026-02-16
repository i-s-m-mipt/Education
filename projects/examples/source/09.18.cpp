///////////////////////////////////////////////////////

// chapter : Memory Management

///////////////////////////////////////////////////////

// section : Dynamic Memory

///////////////////////////////////////////////////////

// content : Virtual and Physical Address Spaces
//
// content : Kernel and User Spaces
//
// content : Stack, Heap, Data, BSS and Text Segments
//
// content : Memory Mappings
//
// content : Tools htop and pmap
//
// content : Page Tables
//
// content : Memory Management Unit
//
// content : Segmentation and Page Faults

///////////////////////////////////////////////////////

// support : pmap <PID>

///////////////////////////////////////////////////////

#include <iostream>
#include <print>

///////////////////////////////////////////////////////

int main() 
{
    auto const size = 100'000uz;

//  ---------------------------------------------------

    [[maybe_unused]]        int array_1[size]{};

    [[maybe_unused]] static int array_2[size]{};

//  ---------------------------------------------------

	auto array_3 = new int[100'000'000]{};

//  ---------------------------------------------------

	std::print("main : enter char : "); std::cin.get();

//  ---------------------------------------------------

    delete[] array_3;
}

///////////////////////////////////////////////////////