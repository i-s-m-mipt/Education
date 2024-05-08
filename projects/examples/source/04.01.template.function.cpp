#include <iostream>
#include <type_traits>

//  ================================================================================================

template < typename T > [[nodiscard]] inline T max_v1(T x, T y)
{
	return (x < y ? y : x);
}

template < typename T1, typename T2 > [[nodiscard]] inline T1 max_v2(T1 x, T2 y) 
{
	return (x < y ? y : x);
}

template < typename T1, typename T2, typename RT > [[nodiscard]] inline RT max_v3(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename RT, typename T1, typename T2 > [[nodiscard]] inline RT max_v4(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename RT = int, typename T1, typename T2 > [[nodiscard]] inline RT max_v5(T1 x, T2 y)
{
	return (x < y ? y : x);
}

template < typename T1, typename T2 > [[nodiscard]] inline auto max_v6(T1 x, T2 y)
{
	return (x < y ? y : x);
}

[[nodiscard]] inline auto max_v7(auto x, auto y)
{
	return (x < y ? y : x);
}

//  ================================================================================================

template < typename T > inline void f(T)
{
	std::cout << "template < T > f(T)" << std::endl;
}

template <> inline void f < int > (int)
{
	std::cout << "template <> f < int > (int)" << std::endl;
}

inline void f(char  ) { std::cout << "f(char  )" << std::endl; }
inline void f(int   ) { std::cout << "f(int   )" << std::endl; }
inline void f(double) { std::cout << "f(double)" << std::endl; }

//  ================================================================================================

template < typename T1, typename T2 > inline void g()
{
	std::cout << "template < T1, T2 > g()" << std::endl;
}

/*
template < typename T > inline void g < int, T > () // error
{
	std::cout << "template < T > g < int, T > ()" << std::endl;
}
*/

//  ================================================================================================

template < typename T > inline void h(T)
{
	std::cout << "template < T > h(T)" << std::endl;
}

template <> inline void h < int * > (int *)
{ 
	std::cout << "template <> h < int * > (int *)" << std::endl;
} 

template < typename T > inline void h(T *)
{
	std::cout << "template < T > h(T *)" << std::endl;
}

//  ================================================================================================

template < typename T, int N, int M > [[nodiscard]] inline bool less(T(&array_1)[N], T(&array_2)[M])
{
	for (auto i = 0; i < N && i < M; ++i)
	{
		if (array_1[i] != array_2[i]) return (array_1[i] < array_2[i]);
	}

	return (N < M);
}

//  ================================================================================================

int main()
{
	std::cout << max_v1('a', 'b') << std::endl;
	std::cout << max_v1(100, 200) << std::endl;
	std::cout << max_v1(1.0, 2.0) << std::endl;
	
//	std::cout << max_v1(1.0, 200) << std::endl; // error

	std::cout << max_v1(1.0, static_cast < double > (200)) << std::endl;

	std::cout << max_v1 < double > (1.0, 200) << std::endl;

	std::cout << max_v2(1.0, 200) << std::endl;
	std::cout << max_v2(100, 2.0) << std::endl; 

	std::cout << max_v3 < int, double, double > (100, 2.0) << std::endl;

	std::cout << max_v4 < double > (100, 2.0) << std::endl;

	std::cout << max_v5(100, 2.0) << std::endl;
	std::cout << max_v6(100, 2.0) << std::endl;
	std::cout << max_v7(100, 2.0) << std::endl;

//  ================================================================================================

	f            ('a');
	f            (100);
	f            (1.0);
	f <        > (100);
	f < int    > (100);
	f <        > (1.0);
	f < double > (1.0);

//  ================================================================================================

	int * ptr = nullptr; h(ptr); // support: пример Димова-Абрамса

//  ================================================================================================

	const int array_1[]{ 1, 2, 3 };
	const int array_2[]{ 1, 2, 3, 4, 5 };

	std::cout << less(array_1, array_2) << std::endl;

	return 0;
}