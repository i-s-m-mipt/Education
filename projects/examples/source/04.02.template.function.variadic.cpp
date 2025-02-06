#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1() {}

template < typename T, typename ... Ts > void test_v1(T x, Ts ... xs)
{
	std::cout << "test_v1 : x = " << x << ' ';
	
	std::cout << "sizeof...(xs) = " << sizeof...(xs) << '\n';
	
	test_v1(xs...); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > void test_v2(T x)
{
	std::cout << "test_v2 : x = " << x << ' ';
}

template < typename T, typename ... Ts > void test_v2(T x, Ts ... xs)
{
	test_v2(x);

	std::cout << "sizeof...(xs) = " << sizeof...(xs) << '\n';

	test_v2(xs...);

	if (sizeof...(xs) == 1)
	{
		std::cout << "sizeof...(xs) = 0\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > void test_v3(Ts ... xs) 
{ 
	test_v1(xs + xs...); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto reduce_v1(Ts ... xs)
{
	return (... + xs); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v2(Ts ... xs)
{
	return (xs + ...); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v3(Ts ... xs)
{
	return (0 + ... + xs); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v4(Ts ... xs)
{
	return (xs + ... + 0); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto make_entity(Ts ... xs)
{
	return new Entity(xs...);
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		test_v1(1, 2, 3);
		
		test_v2(1, 2, 3);

		test_v3(1, 2, 3);
	}
	
//  -----------------------------------------

	{
		assert(reduce_v1(1, 2, 3) == 6);
		
		assert(reduce_v2(1, 2, 3) == 6);

		assert(reduce_v3(1, 2, 3) == 6);

		assert(reduce_v4(1, 2, 3) == 6);
	}
	
//  -----------------------------------------

	{
		delete make_entity(1, 1);
	}	
}