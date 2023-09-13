#include <iostream>

int main()
{
	auto x = 0;
	
//	int & ri; // error: uninitialized reference

	auto & rx = x; // attention: non-constant reference

	rx = 42;

	auto y = 1;

	rx = y; // attention: rx refers to x, not y

	const auto & rcx = x; // attention: constant reference

	const auto & rcv = 42; // attention: lifetime extension 

	return 0;
}