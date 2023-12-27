#include <functional>
#include <iostream>
#include <vector>

int main()
{
	auto x = 0;
	
//	int & ri; // error: uninitialized reference

	auto & rx = x; // note: non-constant reference

	rx = 42;

	auto y = 1;

	rx = y; // note: rx refers to x, not y

	[[maybe_unused]] const auto & rcx = x; // note: constant reference

//	rcx = 42; // error: constant reference

	[[maybe_unused]] const auto & rcv = 42; // note: temporary object lifetime extension 

//	auto & rv = 42; // error: cannot bind to temporary object

//	std::vector < int & > bad_vector; // error: invalid array of references

	std::vector < std::reference_wrapper < int > > good_vector;

	good_vector.push_back(x);

	std::cout << x << ' ' << good_vector.back() << std::endl; x = 2;
	std::cout << x << ' ' << good_vector.back() << std::endl;

	return 0;
}