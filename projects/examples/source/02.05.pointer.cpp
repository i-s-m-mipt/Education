#include <cassert>
#include <iostream>

int main()
{
	int       i =  1;
	int * ptr_i = &i; // support: compiler-explorer.com

	std::cout << "ptr_i = " << ptr_i << std::endl;

	assert(*ptr_i == i);

//	[[maybe_unused]] int * pointer = &i, value = &i; // error

//  ================================================================================================

//	[[maybe_unused]] int * null_ptr_1 =    0; // bad

//	[[maybe_unused]] int * null_ptr_2 = NULL; // bad

	[[maybe_unused]] int * null_ptr_3 = nullptr;

//	*null_ptr_3 = 1; // error

	if (null_ptr_3) *null_ptr_3 = 1;

//  ================================================================================================

	[[maybe_unused]] 	   int               x =  1; 
	[[maybe_unused]] const int               y =  1;

	[[maybe_unused]] 	   int *        ptr__x = &x; 
//	[[maybe_unused]]       int *        ptr__y = &y; // error

	[[maybe_unused]]       int * const cptr__x = &x;
//	[[maybe_unused]]       int * const cptr__y = &y; // error

	[[maybe_unused]] const int *        ptr_cx = &x;
	[[maybe_unused]] const int *        ptr_cy = &y;

	[[maybe_unused]] const int * const cptr_cx = &x;
	[[maybe_unused]] const int * const cptr_cy = &y;

//  ================================================================================================

	[[maybe_unused]]       auto ptr_1 = &x;
	[[maybe_unused]]       auto ptr_2 = &y;
	[[maybe_unused]] const auto ptr_3 = &x;
	[[maybe_unused]] const auto ptr_4 = &y;

	return 0;
}