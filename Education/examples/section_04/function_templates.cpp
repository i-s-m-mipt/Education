#include <iostream>

template < typename T >
T max_v1(T x, T y)
{
	return (x < y ? y : x);
}

template < typename T1, typename T2 >
T1 max_v2(T1 x, T2 y) // note: possible narrow conversion
{
	return (x < y ? y : x);
}

template < typename T1, typename T2, typename RT >
RT max_v3(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename RT, typename T1, typename T2 >
RT max_v4(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename RT = double, typename T1, typename T2 >
RT max_v5(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename T1, typename T2 >
auto max_v6(T1 x, T2 y)
{
	return (x < y ? y : x);
}

auto max_v7(auto x, auto y) // good: compact solution
{
	return (x < y ? y : x);
}

template < typename T >
void f([[maybe_unused]] T value) // note: basic template
{
	std::cout << "template for T" << std::endl;
}

template <>
void f < int > ([[maybe_unused]] int value) // note: full specialization for int
{
	std::cout << "full specialization for int" << std::endl;
}

void f([[maybe_unused]] char value) // note: overload for char
{
	std::cout << "overload for char" << std::endl;
}

void f([[maybe_unused]] int value) // note: overload for double
{
	std::cout << "overload for int" << std::endl;
}

void f([[maybe_unused]] double value) // note: overload for double
{
	std::cout << "overload for double" << std::endl;
}

template < typename T1, typename T2 >
void g([[maybe_unused]] T1 x, [[maybe_unused]] T2 y) // note: basic template
{
	std::cout << "g for T1, T2" << std::endl;
}

/*
template < typename T >
void g < int, T > ([[maybe_unused]] int x, [[maybe_unused]] T y) // error: prohibited partial specialization
{
	std::cout << "g for int, T" << std::endl;
}
*/

int main()
{
	std::cout << max_v1('a', 'b') << std::endl;
	std::cout << max_v1(100, 200) << std::endl;
	std::cout << max_v1(1.0, 2.0) << std::endl;
	
//	std::cout << max_v1(1.0, 200) << std::endl; // error: unresolved template

	std::cout << max_v1(1.0, static_cast < double > (200)) << std::endl;

	std::cout << max_v1 < double > (1.0, 200) << std::endl;

	std::cout << max_v2(1.0, 200) << std::endl;

//	std::cout << max_v2(100, 2.0) << std::endl; // warning: narrow conversion

	std::cout << max_v3 < int, double, double > (100, 2.0) << std::endl;

	std::cout << max_v4 < double > (100, 2.0) << std::endl;

	std::cout << max_v5(100, 2.0) << std::endl;

	std::cout << max_v6(100, 2.0) << std::endl;

	std::cout << max_v7(100, 2.0) << std::endl;

	f            ('a'); // note: overload for char
	f            (100); // note: overload for int
	f            (1.0); // note: overload for double
	f <>         (100); // note: full specialization for int
	f < int >    (100); // note: full specialization for int
	f <>         (1.0); // note: template for T
	f < double > (1.0); // note: template for T

	return 0;
}