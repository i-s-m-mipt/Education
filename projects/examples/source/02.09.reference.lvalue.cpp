#include <functional>
#include <iostream>
#include <vector>

int main()
{
	      auto x = 42;
	const auto y = 42;
	
//	int & ri;     // error
//	int & ry = y; // error

	auto & rx = x; rx = 42; rx = y;

	[[maybe_unused]] const auto & rcy = y;

//	rcy = 42; // error

	[[maybe_unused]] const auto & rcv = 42;

//	auto & rv = 42; // error

//  ================================================================================================

//	std::vector < int & > bad_vector; // error

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	good_vector.back().get() = 2;

	std::cout << x << std::endl; 

	return 0;
}