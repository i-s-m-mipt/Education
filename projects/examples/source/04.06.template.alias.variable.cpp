#include <iostream>

//  ================================================================================================

template < typename T, auto N > class Container {};

template < typename T > using Buffer = Container < T, 1024 > ;

//  ================================================================================================

template < typename T > inline const T pi = T(3.141592);

template < typename T > [[nodiscard]] inline T area(T radius)
{
	return pi < T > * radius * radius; // note: example from standard
}

//  ================================================================================================

int main()
{
	[[maybe_unused]] const Buffer < int > buffer;

//  ================================================================================================

	std::cout << area(1  ) << std::endl;
	std::cout << area(1.0) << std::endl;

	return 0;
}