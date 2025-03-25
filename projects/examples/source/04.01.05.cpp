#include <iostream>

/////////////////////////////////////////////////////////////////////

void test_v1() 
{
	std::cout << "test_v1\n";
}

/////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void test_v1(T x, Ts ... xs)
{
	std::cout << "test_v1 : x = " << x << ' ';
	
	std::cout << "sizeof...(xs) = " << sizeof...(xs) << '\n';
	
	test_v1(xs...); // support : cppinsights.io
}

/////////////////////////////////////////////////////////////////////

template < typename T > void test_v2(T x)
{
	std::cout << "test_v2 : x = " << x << ' ';
}

/////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////

template < typename ... Ts > void test_v3(Ts ... xs) 
{ 
	test_v1(xs + xs...); // support : cppinsights.io
}

/////////////////////////////////////////////////////////////////////

struct Entity 
{ 
	int x = 0, y = 0;
};

/////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto make_entity(Ts ... xs)
{
	return new Entity(xs...);
}

/////////////////////////////////////////////////////////////////////

int main()
{
	test_v1(1, 2, 3);
		
	test_v2(1, 2, 3);

	test_v3(1, 2, 3);

//  -------------------------

    delete make_entity(1, 1);
}