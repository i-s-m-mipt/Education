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
auto max_v6(T1 x, T2 y) // good: compact solution
{
	return (x < y ? y : x);
}

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

	return 0;
}