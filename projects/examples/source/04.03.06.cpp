#include <iostream>

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void test(T x, Ts ... xs)
{
	std::cout << "test_v3 : x = " << x << ' ';
	
	std::cout << "sizeof...(xs) = " << sizeof...(xs) << '\n';

	if constexpr (sizeof...(xs) > 0) 
	{
		test(xs...);
	}
}

//////////////////////////////////////////////////////////////////

int main()
{
	test(1, 2, 3);
}