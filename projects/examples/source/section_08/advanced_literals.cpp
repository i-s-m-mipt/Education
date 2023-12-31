#include <chrono>
#include <iostream>
#include <numbers>

struct Kilometers // note: user-defined units
{
	unsigned long long n;

}; // struct Kilometers

namespace literals // good: namespace for user-defined literals
{
	constexpr auto operator""_km(unsigned long long kilometers) // note: underscore required
	{
		return Kilometers{ kilometers };
	}

	constexpr auto operator""_deg_to_rad(long double degrees) // note: underscore required
	{
		return degrees * std::numbers::pi_v < long double > / 180.0;
	}

	constexpr int pow(int x, int n)
	{
		return (n > 0) ? x * pow(x, n - 1) : 1;
	}

	template < char digit, char ... tail > constexpr auto b3_handler()
	{
		if constexpr (auto x = digit - '0'; sizeof...(tail) > 0)
		{
			return x * pow(3, sizeof...(tail)) + b3_handler < tail... > ();
		}
		else
		{
			return x;
		}
	}

	template < char ... digits > constexpr auto operator""_b3() // note: underscore required
	{
		return b3_handler < digits... > ();
	}

} // namespace literals

int main()
{
	using namespace std::literals; // note: std::chrono, std::complex, std::string

	auto duration = 600s; // note: auto -> std::chrono::seconds

	using namespace literals;

	auto distance = 5_km; // note: auto -> kilometers

	std::cout << 90.0_deg_to_rad << std::endl;

	std::cout << 210_b3 << std::endl; // note: ternary literal

	return 0;
}