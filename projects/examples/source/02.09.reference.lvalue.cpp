#include <cassert>
#include <functional>
#include <vector>

/////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto x = 1; const auto y = 2;

//		[[maybe_unused]] int & ref_1; // error

		[[maybe_unused]] int & r_x = x; // support: compiler-explorer.com

//		[[maybe_unused]] int & r_y_1 = y; // error

		[[maybe_unused]] const int & r_y_2 = y;

		r_x = 2;
		
		assert(x == 2);

//		r_y_2 = 3; // error

//		[[maybe_unused]]       int & ref_2 = 1; // error

		[[maybe_unused]] const int & ref_3 = 1;
	}
	
//  ---------------------------------------------------------------------

	{
		auto x = 1; const auto y = 2;

		[[maybe_unused]]       auto & r_x_1 = x;

		[[maybe_unused]]       auto & r_y_1 = y;

		[[maybe_unused]] const auto & r_x_2 = x;

		[[maybe_unused]] const auto & r_y_2 = y;
	}

//  ---------------------------------------------------------------------

	{
		auto x = 1;

//		std::vector < int & > vector; // error

		std::vector < std::reference_wrapper < int > > vector;

		vector.push_back(x);

		vector.back().get() = 2;
	
		assert(x == 2);
	}
}