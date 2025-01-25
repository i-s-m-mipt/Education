#include <cassert>
#include <format>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto x = 1; [[maybe_unused]] const auto y = 2;

		[[maybe_unused]] int * p_x = &x; // support: compiler-explorer.com

//		[[maybe_unused]] int * p_y = &y; // error

		std::cout << "main : p_x = " << std::format("{:018}", static_cast < void * > (p_x)) << '\n';

		assert(*p_x == x);

//		[[maybe_unused]] int * ptr_1 = &x, ptr_2 = &x; // error
	}

//  ------------------------------------------------------------------------------------------------

	{
//		[[maybe_unused]] int * ptr_1 = 0; // bad

//		[[maybe_unused]] int * ptr_2 = NULL; // bad

		[[maybe_unused]] int * ptr_3 = nullptr;

//		*ptr_3 = 1; // error
	}

//  ------------------------------------------------------------------------------------------------

	{
		auto x = 1; const auto y = 2;

		[[maybe_unused]]       auto p_x_1 = &x;
		
		[[maybe_unused]]       auto p_y_1 = &y;

		[[maybe_unused]] const auto p_x_2 = &x;

		[[maybe_unused]] const auto p_y_2 = &y;
	}
	
//  ------------------------------------------------------------------------------------------------

	{
		auto x = 1; const auto y = 2;

		[[maybe_unused]]       int * const cp_x = &x;

//		[[maybe_unused]]       int * const cp_y = &y; // error

		[[maybe_unused]] const int *        pcx = &x;

		[[maybe_unused]] const int *        pcy = &y;

		[[maybe_unused]] const int * const cpcx = &x;

		[[maybe_unused]] const int * const cpcy = &y;
	}
}