#include <cassert>
#include <functional>
#include <vector>

///////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto x = 1; const auto y = 2;

//		[[maybe_unused]]       int & r_x    ; // error

//		[[maybe_unused]]       int & r_y = y; // error

		[[maybe_unused]]       int & r_x = x; // support: compiler-explorer.com

		[[maybe_unused]] const int & rcy = y;

		r_x = 2; assert(x == 2);

//		rcy = 3; // error

//		[[maybe_unused]]       int & r_i = 1; // error

		[[maybe_unused]] const int & rci = 1;
	}
	
//  ===========================================================================

	{
		auto x = 1; const auto y = 2;

		[[maybe_unused]]       auto & r_x_1 = x;

		[[maybe_unused]]       auto & r_y_1 = y;

		[[maybe_unused]] const auto & r_x_2 = x;

		[[maybe_unused]] const auto & r_y_2 = y;
	}

//  ===========================================================================

	{
		auto x = 1;

//		std::vector < int & > vector_1; // error

		std::vector < std::reference_wrapper < int > > vector_2;

		vector_2.push_back(x);

		vector_2.back().get() = 2; 
	
		assert(x == 2);
	}
}