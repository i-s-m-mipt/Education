/////////////////////////////////////////////////////////////

// chapter : Projects and Libraries

/////////////////////////////////////////////////////////////

// content : Internal and External Linking
//
// content : Multiply Defined and Unresolved External Symbols
//
// content : Global, Local, Weak and Unique Symbols
//
// content : Tools readelf and grep
//
// content : Link-Time Optimization (LTO)
//
// content : Options -l, -flto=auto and -fwhole-program

/////////////////////////////////////////////////////////////

// support : readelf -s 06.08.o | grep -E "test_v1|g_x1"
//
// support : readelf -s 06.08.o | grep -E "test_v4|g_x2"
//
// support : readelf -s 06.08.o | grep test_v5
//
// support : readelf -s 06.08.o | grep g_x3

/////////////////////////////////////////////////////////////

#include <cassert>
#include <print>

/////////////////////////////////////////////////////////////

#include "06.05.hpp"
#include "06.06.hpp"

/////////////////////////////////////////////////////////////

// void test_v1() // error
// {
//     std::print("test_v1\n");
// }

/////////////////////////////////////////////////////////////

int main()
{
	test_v1();

//	test_v2(); // error

//	test_v3(); // error

	test_v4();

	test_v5();

//  -------------------

	test_v6 < int > ();

//  -------------------

	assert(g_x1 == 1);

	assert(g_x2 == 2);

	assert(g_x3 == 3);
}

/////////////////////////////////////////////////////////////