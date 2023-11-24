#include <iostream>
#include <type_traits>

constexpr auto is_prime(int p) // note: can be computed at compile-time
{
	for (auto d = 2; d <= p / 2; ++d)
	{
		if (p % d == 0)
		{
			return false;
		}
	}

	return (p > 1);
}

constexpr auto f([[maybe_unused]] int x)
{
	return std::is_constant_evaluated(); // note: see type traits
}

template < typename T, typename ... Types > void print(const T & arg, const Types & ... args)
{
	std::cout << arg << std::endl;

	if constexpr (sizeof...(args) > 0) // note: compile-time instantiation
	{
		print(args...);
	}
}

int main()
{
	constexpr auto x = 42; // note: compile-time constant

	[[maybe_unused]] constexpr auto is_prime_1 = is_prime(5); // note: compile-time
	[[maybe_unused]] constexpr auto is_prime_2 = is_prime(x); // note: compile-time

	auto y = 43;

//	constexpr auto is_prime_3 = is_prime(y); // error: not compile-time constant

	[[maybe_unused]] auto is_prime_4 = is_prime(5); // note: can be computed at compile-time
	[[maybe_unused]] auto is_prime_5 = is_prime(x); // note: can be computed at compile-time

	[[maybe_unused]] auto is_prime_6 = is_prime(y); // note: runtime only

	constexpr auto result = f(x);

	std::cout << result << ' ' << f(y) << std::endl;

	print('a', 42, 3.14);

	return 0;
}