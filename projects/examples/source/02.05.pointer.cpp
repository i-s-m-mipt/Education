#include <cassert>
#include <iostream>

int main()
{
	auto x = 1; const auto y = 2;
	
//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]] int * p_x = &x; // support: compiler-explorer.com

//	[[maybe_unused]] int * p_y = &y; // error

	std::cout << "p_x = " << p_x << '\n';

	assert(*p_x == x);

//	[[maybe_unused]] int * ptr = &i, z = &i; // error

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]]       int * const cp_x = &x;
//	[[maybe_unused]]       int * const cp_y = &y; // error

	[[maybe_unused]] const int *        pcx = &x;
	[[maybe_unused]] const int *        pcy = &y;

	[[maybe_unused]] const int * const cpcx = &x;
	[[maybe_unused]] const int * const cpcy = &y;

//  ------------------------------------------------------------------------------------------------

	[[maybe_unused]]       auto ap_x_1 = &x;
	[[maybe_unused]]       auto ap_y_1 = &y;
	[[maybe_unused]] const auto ap_x_2 = &x;
	[[maybe_unused]] const auto ap_y_2 = &y;

//  ------------------------------------------------------------------------------------------------

//	[[maybe_unused]] int * null_ptr_1 = 0; // bad

//	[[maybe_unused]] int * null_ptr_2 = NULL; // bad

	[[maybe_unused]] int * null_ptr_3 = nullptr;

//	*null_ptr_3 = 1; // error

	if (null_ptr_3) 
	{
		std::cout << "*null_ptr_3 = " << *null_ptr_3 << '\n';
	}
}