/////////////////////////////////////////////////////////////////////////////////////////

// chapter : Applied Computations

/////////////////////////////////////////////////////////////////////////////////////////

// content : Floating-Point Numbers
//
// content : Standard IEEE 754
//
// content : Sign, Mantissa and Exponent
//
// content : Precision Problem
//
// content : Infinity and Not-A-Number (NAN)
//
// content : Quiet and Signaling NANs

/////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <format>
#include <limits>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	for (auto i = 1uz; i < std::numeric_limits < double > ::digits10 + 1; ++i)
	{
		assert(std::format("{:.{}f}", 1.0, i) == "1." + std::string(i, '0'));
	}

//  -------------------------------------------------------------------------------------

	for (auto i = 0uz; i < std::numeric_limits < double > ::max_exponent10 + 1; ++i)
	{
		auto string = (i < 10 ? "0" : "") + std::to_string(i);

	//  -----------------------------------------------------------------------

		assert(std::format("{:.{}e}", std::pow(10.0, i), 0) == "1e+" + string);
	}

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_infinity )
	{
		assert(std::format("{}", std::numeric_limits < double > ::infinity ()) == "inf");
	}

//  -------------------------------------------------------------------------------------

	if (std::numeric_limits < double > ::has_quiet_NaN)
	{
		assert(std::format("{}", std::numeric_limits < double > ::quiet_NaN()) == "nan");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////