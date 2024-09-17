#include <cassert>
#include <functional>
#include <vector>

int main()
{
	[[maybe_unused]]       int     x = 1;
	[[maybe_unused]] const int     y = 1;
	
//	[[maybe_unused]]       int &  ri    ; // error
//	[[maybe_unused]]       int &  ry = y; // error

	[[maybe_unused]]       int &  rx = x; rx = 2; assert(x == 2);
	[[maybe_unused]] const int & cry = y;

//	cry = 2; // error

//	[[maybe_unused]]       int &  rv = 1; // error
	[[maybe_unused]] const int & crv = 1;

//  ================================================================================================

	[[maybe_unused]]       auto & test_1 = x;
	[[maybe_unused]]       auto & test_2 = y;
	[[maybe_unused]] const auto & test_3 = x;
	[[maybe_unused]] const auto & test_4 = y;

//  ================================================================================================

//	std::vector < int & > bad_vector; // error

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 1; assert(x == 1);

	return 0;
}