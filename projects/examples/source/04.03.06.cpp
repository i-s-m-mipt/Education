//////////////////////////////////////////////////////////////////

#include <iostream>

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void test(T x, Ts ... ys)
{
	std::cout << "test_v3 : x = " << x << ' ';

//  ---------------------------------------------------------
	
	std::cout << "sizeof...(ys) = " << sizeof...(ys) << '\n';

//  ---------------------------------------------------------

	if constexpr (sizeof...(ys) > 0) 
	{
		test(ys...);
	}
}

//////////////////////////////////////////////////////////////////

int main()
{
	test(1, 2, 3);
}

//////////////////////////////////////////////////////////////////