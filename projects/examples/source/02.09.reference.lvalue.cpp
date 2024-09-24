#include <cassert>
#include <functional>
#include <vector>

int main()
{
	[[maybe_unused]]       int        x = 1;
	[[maybe_unused]] const int        y = 1;
	
//	[[maybe_unused]]       int & ref__i    ; // error
//	[[maybe_unused]]       int & ref__y = y; // error

	[[maybe_unused]]       int & ref__x = x; ref__x = 2; assert(x == 2);
	[[maybe_unused]] const int & ref_cy = y;

//	ref_cy = 2; // error

//	[[maybe_unused]]       int & ref__v = 1; // error
	[[maybe_unused]] const int & ref_cv = 1;

//  ================================================================================================

	[[maybe_unused]]       auto & ref_1 = x;
	[[maybe_unused]]       auto & ref_2 = y;
	[[maybe_unused]] const auto & ref_3 = x;
	[[maybe_unused]] const auto & ref_4 = y;

//  ================================================================================================

//	std::vector < int & > bad_vector; // error

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 3; assert(x == 3);

	return 0;
}