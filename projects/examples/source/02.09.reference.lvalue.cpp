#include <functional>
#include <iostream>
#include <vector>

int main()
{
	[[maybe_unused]]       int     x = 42;
	[[maybe_unused]] const int     y = 42;
	
//	[[maybe_unused]]       int &  ri     ; // error
//	[[maybe_unused]]       int &  ry =  y; // error

	[[maybe_unused]]       int &  rx =  x; rx = 42;
	[[maybe_unused]] const int & cry =  y;

//	[[maybe_unused]]       int &  rv = 42; // error
	[[maybe_unused]] const int & crv = 42;

//	cry = 42; // error
//	crv = 42; // error

//  ================================================================================================

	[[maybe_unused]]       auto & test_1 = x;
	[[maybe_unused]]       auto & test_2 = y;
	[[maybe_unused]] const auto & test_3 = x;
	[[maybe_unused]] const auto & test_4 = y;

//  ================================================================================================

//	std::vector < int & > bad_vector; // error

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 42;

	std::cout << x << std::endl; 

	return 0;
}