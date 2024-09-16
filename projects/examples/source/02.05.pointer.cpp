#include <cassert>
#include <iostream>

int main()
{
	int       i =  1;
	int * ptr_i = &i;

	std::cout << "ptr_i = " << ptr_i << std::endl;

	assert(*ptr_i == 1);

//	[[maybe_unused]] int * pointer = &i, value = &i; // error

//  ================================================================================================

//	[[maybe_unused]] int * ptr_null_1 = 0; // bad

	[[maybe_unused]] int * ptr_null_2 = nullptr;

//	[[maybe_unused]] auto  ptr_null_3 = nullptr; // bad 

//	*ptr_null_2 = 1; // error

	if (ptr_null_2) *ptr_null_2 = 1;

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

	[[maybe_unused]]       auto test_1 = &x;
	[[maybe_unused]]       auto test_2 = &y;
	[[maybe_unused]] const auto test_3 = &x;
	[[maybe_unused]] const auto test_4 = &y;

	return 0;
}