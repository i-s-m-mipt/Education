#include <iostream>

int main()
{
	auto x = 0;
	
//	int & ri; // error: uninitialized reference

	auto & rx = x; // note: non-constant reference

	rx = 42;

	auto y = 1;

	rx = y; // note: rx refers to x, not y

	const auto & rcx = x; // note: constant reference

//	rcx = 42; // error: constant reference

	const auto & rcv = 42; // note: temporary object lifetime extension 

//	auto & rv = 42; // error: cannot bind to temporary object

	return 0;
}