#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////////////

constexpr auto factorial_v1(unsigned int x) -> unsigned int
{
	return x > 1 ? x * factorial_v1(x - 1) : 1u;
}

consteval auto factorial_v2(unsigned int x) -> unsigned int
{
	return x > 1 ? x * factorial_v2(x - 1) : 1u;
}

///////////////////////////////////////////////////////////////////////////////////////////////

consteval auto is_prime(unsigned int x)
{
	for (auto i = 2u; i * i < x; ++i)
	{
		if (x % i == 0) 
		{
			return false;
		}
	}

	return x > 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////

consteval auto test_v1()
{
//	[[maybe_unused]] auto object = new auto(1); // error

	std::vector < int > vector({ 1, 2, 3, 4, 5 });

	return std::ranges::fold_left(vector, 0, std::plus <> ());
}

///////////////////////////////////////////////////////////////////////////////////////////////

constexpr auto test_v2(int) 
{ 
	return std::is_constant_evaluated(); 
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > void test_v3(T arg, Ts ... args)
{
	std::cout << "test_v3 : arg = " << arg << ' ';
	
	std::cout << "sizeof...(args) = " << sizeof...(args) << '\n';

	if constexpr (sizeof...(args) > 0) 
	{
		test_v3(args...);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

constinit auto global_x = 1;

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	constexpr auto x = 5; auto y = 5;

//  ---------------------------------------------------------------------------------------

	[[maybe_unused]] constexpr auto z1 = factorial_v1(x);
//	[[maybe_unused]] constexpr auto z2 = factorial_v1(y); // error

	[[maybe_unused]]           auto z3 = factorial_v1(x); // support: compiler-explorer.com
	[[maybe_unused]]           auto z4 = factorial_v1(y);

	[[maybe_unused]] constexpr auto z5 = factorial_v2(x);
//	[[maybe_unused]] constexpr auto z6 = factorial_v2(y); // error

	[[maybe_unused]]           auto z7 = factorial_v2(x);
//	[[maybe_unused]]           auto z8 = factorial_v2(y); // error

//  ---------------------------------------------------------------------------------------

	static_assert(is_prime(x) && test_v1() == 15);

//  ---------------------------------------------------------------------------------------

	constexpr auto is_constant_evaluated_1 = test_v2(x);
	
		      auto is_constant_evaluated_2 = test_v2(y);

	assert(is_constant_evaluated_1 && !is_constant_evaluated_2);

//  ---------------------------------------------------------------------------------------

	test_v3(1, 2, 3);

//  ---------------------------------------------------------------------------------------

	assert(++global_x == 2);
}