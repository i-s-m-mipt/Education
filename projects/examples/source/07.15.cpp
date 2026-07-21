/////////////////////////////////////////////////

// chapter : Debugging and Profiling Tools

/////////////////////////////////////////////////

// content : Debugging
//
// content : Address Sanitizers
//
// content : Heap-Buffer-Overflow Errors
//
// content : Memory Leaks
//
// content : Use-After-Free Errors
//
// content : Option -fsanitize=address
//
// content : Tool valgrind

/////////////////////////////////////////////////

// support : valgrind --leak-check=yes ./07.15.02

/////////////////////////////////////////////////

#include <cassert>

/////////////////////////////////////////////////

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

/////////////////////////////////////////////////