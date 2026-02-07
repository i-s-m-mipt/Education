/////////////////////////////////////////////

// chapter : Debugging and Profiling

/////////////////////////////////////////////

// section : Software Analysis Tools

/////////////////////////////////////////////

// content : Address Sanitizers
//
// content : Heap-Buffer-Overflow Errors
//
// content : Memory Leaks
//
// content : Use-After-Free Errors

/////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////

int main() 
{
	auto array = new int[5]{ 1, 2, 3, 4, 5 };

//  -----------------------------------------

	assert(array[5] == 0);

//  -----------------------------------------

//  delete[] array; // error

//  -----------------------------------------

    assert(array[0] == 1);
}

/////////////////////////////////////////////