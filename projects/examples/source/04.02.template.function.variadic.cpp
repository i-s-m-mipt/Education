#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1() {}

template < typename T, typename ... Ts > void test_v1(T arg, Ts ... args)
{
	std::cout << "test_v1 : arg = " << arg << ' ';
	
	std::cout << "sizeof...(args) = " << sizeof...(args) << '\n';
	
	test_v1(args...); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > void test_v2(T arg)
{
	std::cout << "test_v2 : arg = " << arg << ' ';
}

template < typename T, typename ... Ts > void test_v2(T arg, Ts ... args)
{
	test_v2(arg);

	std::cout << "sizeof...(args) = " << sizeof...(args) << '\n';

	test_v2(args...);

	if (sizeof...(args) == 1)
	{
		std::cout << "sizeof...(args) = 0\n";
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > void test_v3(Ts ... args) 
{ 
	test_v1(args + args...); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto reduce_v1(Ts ... args)
{
	return (... + args); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v2(Ts ... args)
{
	return (args + ...); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v3(Ts ... args)
{
	return (0 + ... + args); // support: cppinsights.io
}

template < typename ... Ts > auto reduce_v4(Ts ... args)
{
	return (args + ... + 0); // support: cppinsights.io
}

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int data_1 = 0, data_2 = 0; 
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > auto make_object(Ts ... args)
{
	return new T(args...);
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
		delete make_object < Entity > (1, 1);
	}	
}