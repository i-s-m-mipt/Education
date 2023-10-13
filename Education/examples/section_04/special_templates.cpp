#include <iostream>

template < typename T, int N >
class basic_stack{};

template < typename T >
using Stack = basic_stack < T, 1024 > ; // note: alias template

template < typename T >
const T pi = T(3.141592); // note: variable template

template < typename T >
T area(T r)
{
	return pi < T > * r * r;
}

int main()
{
	[[maybe_unused]] Stack < int > stack;

	std::cout << area(100) << std::endl;
	std::cout << area(1.0) << std::endl;

	return 0;
}