#include <cassert>
#include <cmath>
#include <numbers>

//  ================================================================================================

struct Weight 
{ 
	unsigned long long kilograms = 0; 
};

//  ================================================================================================

namespace literals
{
	auto operator""_kg(unsigned long long kilograms)
	{
		return Weight(kilograms);
	}

//  ------------------------------------------------------------------------------------------------

	auto operator""_deg_to_rad(long double degrees)
	{
		return degrees * std::numbers::pi_v < long double > / 180.0;
	}

//  ------------------------------------------------------------------------------------------------

	namespace detail
	{
		auto pow(int x, unsigned int y) -> int
		{
			return y > 0 ? x * pow(x, y - 1) : 1;
		}

		template < char D, char ... Ds > auto b3_handler() -> int
		{
			if constexpr (auto x = D - '0'; sizeof...(Ds) > 0)
			{
				return x * pow(3, sizeof...(Ds)) + b3_handler < Ds... > ();
			}
			else
			{
				return x;
			}
		}
	}
	
//  ------------------------------------------------------------------------------------------------

	template < char ... Ds > auto operator""_b3()
	{
		return detail::b3_handler < Ds... > ();
	}
}

using namespace literals;

//  ================================================================================================

int main()
{
	[[maybe_unused]] auto weight = 5_kg;

	assert(std::abs(180.0_deg_to_rad - std::numbers::pi) < 1e-6);

	assert(210_b3 == 21);
}