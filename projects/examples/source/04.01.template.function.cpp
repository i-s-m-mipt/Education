#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

//  ================================================================================================

template < typename T > T max_v1(T x, T y) // support: cppinsights.io
{
	return x < y ? y : x;
}

template < typename T1, typename T2 > T1 max_v2(T1 x, T2 y) 
{
	return x < y ? y : x;
}

template < typename T1, typename T2, typename RT > RT max_v3(T1 x, T2 y)
{
	return x < y ? y : x;
}

template < typename RT, typename T1, typename T2 > RT max_v4(T1 x, T2 y)
{
	return x < y ? y : x;
}

template < typename RT = double, typename T1, typename T2 > RT max_v5(T1 x, T2 y)
{
	return x < y ? y : x;
}

template < typename T1, typename T2 > std::common_type_t < T1, T2 > max_v6(T1 x, T2 y)
{
	return x < y ? y : x;
}

template < typename T1, typename T2 > auto max_v7(T1 x, T2 y)
{
	return x < y ? y : x;
}

auto max_v8(auto x, auto y) // support: cppinsights.io
{
	return x < y ? y : x;
}

//  ================================================================================================

template < typename T > void test_v1(T)
{
	std::cout << "test_v1 (1)\n";
}

template <> void test_v1 < int > (int)
{
	std::cout << "test_v1 (2)\n";
}

void test_v1(int) 
{ 
	std::cout << "test_v1 (3)\n"; 
}

void test_v1(double) 
{ 
	std::cout << "test_v1 (4)\n"; 
}

//  ================================================================================================

template < typename T1, typename T2 > void test_v2()
{
	std::cout << "test_v2 (1)\n";
}

//  template < typename T > void test_v2 < T, double > () // error
//  {
//	  std::cout << "test_v2 (2)\n";
//  }

//  ================================================================================================

template < typename T > void test_v3(T)
{
	std::cout << "test_v3 (1)\n";
}

template < typename T > void test_v3(T *)
{
	std::cout << "test_v3 (2)\n";
}

template <> void test_v3 < int > (int *)
{ 
	std::cout << "test_v3 (3)\n";
} 

//  ================================================================================================

template < typename T > void test_v4(T)
{
	std::cout << "test_v4 (1)\n";
}

template <> void test_v4 < int * > (int *)
{ 
	std::cout << "test_v4 (2)\n";
} 

template < typename T > void test_v4(T *)
{
	std::cout << "test_v4 (3)\n";
}

//  ================================================================================================

template 
< 
	typename T, std::size_t S1, 
				std::size_t S2 
> 
auto max_v9(const T(&array_1)[S1], const T(&array_2)[S2])
{
	for (auto i = 0uz; i < std::min(S1, S2); ++i)
	{
		if (array_1[i] > array_2[i]) { return array_1; }
		if (array_1[i] < array_2[i]) { return array_2; }
	}

	return S1 > S2 ? array_1 : array_2;
}

//  ================================================================================================

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	assert(max_v1(1, 2) == 2);

	assert(equal(max_v1(1.0, 2.0), 2.0));

//	assert(equal(max_v1(1  , 2.0), 2.0)); // error

	assert(equal(max_v1(static_cast < double > (1), 2.0), 2.0));

	assert(equal(max_v1 < double > (1, 2.0), 2.0));

	assert(equal(max_v2(1.0, 2), 2.0));

//	assert(max_v2(1, 2.0) == 2); // bad

	assert(equal(max_v3 < int, double, double > (1, 2.0), 2.0));

	assert(equal(max_v4 < double > (1, 2.0), 2.0));

	assert(equal(max_v5(1, 2.0), 2.0));
	assert(equal(max_v6(1, 2.0), 2.0));
	assert(equal(max_v7(1, 2.0), 2.0));
	assert(equal(max_v8(1, 2.0), 2.0));

	assert(equal(std::max(1.0, 2.0), 2.0));
	
//	assert(equal(std::max(1  , 2.0), 2.0)); // error

//  ------------------------------------------------

	test_v1(1);

	test_v1(1.0);

	test_v1 <> (1);

	test_v1 < int > (1);

	test_v1 <> (1.0);

	test_v1 < double > (1.0);

//  -------------------------

	test_v2 < int, int > ();

//	test_v2 < int, double > (); // error

//  -------------------------

	int * ptr = nullptr; 
	
	test_v3(ptr);

	test_v4(ptr);

//  -------------------------------

	int array_1[]{ 1, 2, 3, 4, 5 };

	int array_2[]{ 1, 2, 3 };

	assert(max_v9(array_1, array_2) == array_1);
}