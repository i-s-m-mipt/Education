#include <functional>
#include <iostream>
#include <vector>

int main()
{
	      auto x = 42;
	const auto y = 42;
	
//	[[maybe_unused]] int  & ri;     // error
//	[[maybe_unused]] int  & ry = y; // error

	[[maybe_unused]]       auto &  rx = x; rx = y;
	[[maybe_unused]] const auto & cry = y;

//	cry = 42; // error

	[[maybe_unused]] const auto & crv = 42;
//	[[maybe_unused]]       auto &  rv = 42; // error

//  ================================================================================================

//	std::vector < int & > bad_vector; // error

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 2;

	std::cout << x << std::endl; 

	return 0;
}