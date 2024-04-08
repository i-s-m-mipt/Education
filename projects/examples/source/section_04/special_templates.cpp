#include <iostream>

template < typename T > inline const T pi = T(3.141592);

template < typename T > [[nodiscard]] inline T area(T r)
{
	return pi < T > * r * r; // note: example from standard
}

template < typename T, auto N > class Container {};

template < typename T > using Buffer = Container < T, 1024 > ;

int main()
{
	std::cout << area(1  ) << std::endl;
	std::cout << area(1.0) << std::endl;

	[[maybe_unused]] const Buffer < int > buffer;

	return 0;
}
