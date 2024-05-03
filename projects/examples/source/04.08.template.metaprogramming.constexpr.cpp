#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

//  ================================================================================================

[[nodiscard]] inline constexpr int factorial(int n) // note: can be evaluated at compile-time
{
	return (n < 2 ? 1 : n * factorial(n - 1));
}

[[nodiscard]] consteval int combination(int m, int n) // note: must be evaluated at compile-time
{
	return factorial(n) / factorial(m) / factorial(n - m);
}

[[nodiscard]] inline constexpr bool is_prime(int p) // note: can be evaluated at compile-time
{
	for (auto d = 2; d <= p / 2; ++d)
	{
		if (p % d == 0) return false;
	}

	return (p > 1);
}

//  ================================================================================================

[[nodiscard]] consteval int fibonacci(int n) // note: must be evaluated at compile-time
{
	if (n < 2) return 1; else
	{
		std::vector < int > vector(n, 1); // note: allowed dynamic allocation

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

class C { static constexpr auto c = 42; }; // note: constexpr here is same as inline const  

//  ================================================================================================

template < typename T, typename ... Ts > inline void print(const T & arg, const Ts & ... args)
{
	if constexpr (std::cout << arg << std::endl; sizeof...(args) > 0) 
	{
		print(args...); // note: compile-time instantiation
	}
}

//  ================================================================================================

constinit auto global_variable = 42; // note: compile-time initialization

//  ================================================================================================

int main()
{
	constexpr auto x = 5; // note: compile-time constant

	std::cout << factorial(x) << std::endl;

	auto y = 42;

//	auto z = combination(x, y); // error: non-compile-time evaluation

//  ================================================================================================

	[[maybe_unused]] constexpr auto is_prime_1 = is_prime(5); // note: compile-time constant
	[[maybe_unused]] constexpr auto is_prime_2 = is_prime(x); // note: compile-time constant

//	constexpr auto is_prime_3 = is_prime(y); // error: non-compile-time constant

	[[maybe_unused]] auto is_prime_4 = is_prime(5); // note: can be evaluated at compile-time
	[[maybe_unused]] auto is_prime_5 = is_prime(x); // note: can be evaluated at compile-time

	[[maybe_unused]] auto is_prime_6 = is_prime(y); // note: runtime variable

//  ================================================================================================

	std::cout << fibonacci(5) << std::endl;

//  ================================================================================================

	constexpr auto result = f(x);

	std::cout << result << ' ' << f(y) << std::endl;

//  ================================================================================================

	print('a', 42, 3.14);

//  ================================================================================================

	std::cout << ++global_variable << std::endl; // note: non-constant global variable

	return 0;
}