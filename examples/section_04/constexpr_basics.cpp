#include <iostream>

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

int main()
{
	constexpr auto x = 43; // note: compile-time constant

	[[maybe_unused]] constexpr auto result_1 = is_prime(5); // note: compile-time
	[[maybe_unused]] constexpr auto result_2 = is_prime(x); // note: compile-time

	auto y = 42;

//	constexpr auto result_3 = is_prime(y); // error: not compile-time constant

	[[maybe_unused]] auto result_4 = is_prime(5); // note: can be computed at compile-time
	[[maybe_unused]] auto result_5 = is_prime(x); // note: can be computed at compile-time

	[[maybe_unused]] auto result_6 = is_prime(y); // note: runtime only

	return 0;
}