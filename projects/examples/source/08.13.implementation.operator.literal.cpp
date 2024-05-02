#include <chrono>
#include <iostream>
#include <numbers>

using namespace std::literals; // note: std::chrono, std::complex, std::string

//  ================================================================================================

struct Kilometers { unsigned long long n{}; }; // note: user-defined units

//  ================================================================================================

namespace literals // good: namespace for user-defined literals
{
	[[nodiscard]] inline constexpr Kilometers operator""_km(unsigned long long kilometers) noexcept
	{
		return Kilometers { kilometers };
	}

	[[nodiscard]] inline constexpr long double operator""_deg_to_rad(long double degrees) noexcept
	{
		return degrees * std::numbers::pi_v < long double > / 180.0;
	}

	[[nodiscard]] inline constexpr int pow(int x, int n) noexcept
	{
		return (n > 0 ? x * pow(x, n - 1) : 1);
	}

	template < char digit, char ... tail > [[nodiscard]] inline constexpr int b3_handler() noexcept
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

	template < char ... digits > [[nodiscard]] inline constexpr int operator""_b3() noexcept
	{
		return b3_handler < digits... > ();
	}

} // namespace literals

using namespace literals;

//  ================================================================================================

int main()
{
	[[maybe_unused]] constexpr auto duration = 600s; // note: auto -> std::chrono::seconds

	[[maybe_unused]] constexpr auto distance = 5_km; // note: auto -> kilometers, underscore required

	std::cout << 90.0_deg_to_rad << std::endl;

	std::cout << 210_b3 << std::endl; // note: ternary literal

	return 0;
}