#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

//  ================================================================================================

[[nodiscard]] constexpr int factorial_v1(int x)
{
	return x <= 1 ? 1 : x * factorial_v1(x - 1);
}

[[nodiscard]] consteval int factorial_v2(int x)
{
	return x <= 1 ? 1 : x * factorial_v2(x - 1);
}

//  ================================================================================================

[[nodiscard]] consteval auto is_prime(int x)
{
	for (auto d = 2; d * d < x; ++d)
	{
		if (x % d == 0) 
		{
			return false;
		}
	}

	return x > 1;
}

//  ================================================================================================

[[nodiscard]] consteval auto test_v1()
{
//	[[maybe_unused]] auto object = new auto(1); // error

	std::vector < int > vector { 1, 2, 3, 4, 5 };

	return std::ranges::fold_left(vector, 0, std::plus <> ());
}

//  ================================================================================================

[[nodiscard]] constexpr auto test_v2(int) 
{ 
	return std::is_constant_evaluated(); 
}

//  ================================================================================================

template < typename T, typename ... Ts > void print(T arg, Ts ... args)
{
	if constexpr (std::cout << arg << ' '; sizeof...(args) > 0) 
	{
		print(args...);
	}
}

//  ================================================================================================

constinit auto global_x = 1;

//  ================================================================================================

int main()
{
	constexpr auto x = 5; auto y = 5;

//  --------------------------------------------------------------

	[[maybe_unused]] constexpr auto factorial_1 = factorial_v1(x);
//	[[maybe_unused]] constexpr auto factorial_2 = factorial_v1(y); // error

	[[maybe_unused]]           auto factorial_3 = factorial_v1(x); // support: compiler-explorer.com
	[[maybe_unused]]           auto factorial_4 = factorial_v1(y);

	[[maybe_unused]] constexpr auto factorial_5 = factorial_v2(x);
//	[[maybe_unused]] constexpr auto factorial_6 = factorial_v2(y); // error

	[[maybe_unused]]           auto factorial_7 = factorial_v2(x);
//	[[maybe_unused]]           auto factorial_8 = factorial_v2(y); // error

//  -----------------------------------------------------------------------

	static_assert(is_prime(x) && test_v1() == 15);

//  ----------------------------------------------------

	constexpr auto is_constant_evaluated_1 = test_v2(x);
		      auto is_constant_evaluated_2 = test_v2(y);

	assert(is_constant_evaluated_1 && !is_constant_evaluated_2);

//  ----------------------------------------------------------------

	std::cout << "args = { "; print(1, "aaaaa"); std::cout << "}\n";

//  ----------------------------------------------------------------

	assert(++global_x == 2);
}