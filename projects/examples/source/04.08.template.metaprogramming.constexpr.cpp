#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

//  ================================================================================================

[[nodiscard]] inline constexpr int factorial(int n)
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

[[nodiscard]] consteval int combination(int m, int n)
{
	return factorial(n) / factorial(m) / factorial(n - m);
}

[[nodiscard]] inline constexpr bool is_prime(int p)
{
	for (auto d = 2; d <= p / 2; ++d)
	{
		if (p % d == 0) return false;
	}

	return (p > 1);
}

//  ================================================================================================

[[nodiscard]] consteval int fibonacci(int n)
{
	if (n < 2) return 1; else
	{
		std::vector < int > vector(n, 1);

		for (std::size_t i = 2; i < std::size(vector); ++i)
		{
			vector[i] = vector[i - 1] + vector[i - 2];
		}

		return vector.back();
	}
}

//  ================================================================================================

[[nodiscard]] inline constexpr bool f(int) { return std::is_constant_evaluated(); }

//  ================================================================================================

class C1 { static        constexpr auto c = 42; };
class C2 { static inline const     auto c = 42; };

//  ================================================================================================

template < typename T, typename ... Ts > inline void print(const T & arg, const Ts & ... args)
{
	if constexpr (std::cout << arg << std::endl; sizeof...(args) > 0) 
	{
		print(args...);
	}
}

//  ================================================================================================

constinit auto global_variable = 42;

//  ================================================================================================

int main()
{
	constexpr auto x = 5;

	std::cout << factorial(x) << std::endl;

	[[maybe_unused]] auto y = 42;

//	[[maybe_unused]] auto z = combination(x, y); // error

//  ================================================================================================

	[[maybe_unused]] constexpr auto is_prime_1 = is_prime(5);
	[[maybe_unused]] constexpr auto is_prime_2 = is_prime(x);
//	[[maybe_unused]] constexpr auto is_prime_3 = is_prime(y); // error

	[[maybe_unused]]           auto is_prime_4 = is_prime(5);
	[[maybe_unused]]           auto is_prime_5 = is_prime(x);
	[[maybe_unused]]           auto is_prime_6 = is_prime(y);

//  ================================================================================================

	std::cout << fibonacci(5) << std::endl;

//  ================================================================================================

	constexpr auto result = f(x);

	std::cout << result << ' ' << f(y) << std::endl;

//  ================================================================================================

	print('a', 42, 3.14);

//  ================================================================================================

	std::cout << ++global_variable << std::endl;

	return 0;
}