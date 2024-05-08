#include <iostream>

int main()
{
	int       z = 42;
	int * ptr_z = &z; 

	std::cout <<  ptr_z << std::endl;
	std::cout << *ptr_z << std::endl;

//	[[maybe_unused]] int * ptr = &z, v = &z; // error

//  ================================================================================================

//	[[maybe_unused]] int * ptr_null_1 = 0; // bad: целочисленный литерал

	[[maybe_unused]] int * ptr_null_2 = nullptr;

//	[[maybe_unused]] auto  ptr_null_3 = nullptr; // bad: std::nullptr_t

//	*ptr_null_2 = 42; // error

	if (ptr_null_2) std::cout << *ptr_null_2 << std::endl;

//  ================================================================================================

	[[maybe_unused]] 	   int               x = 42; 
	[[maybe_unused]] const int               y = 42;

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