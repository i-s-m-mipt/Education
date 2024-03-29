module; // note: global module fragment

#include <cmath>

export module math; // note: interface unit

export import math.submodule;

export void hello_module();

export namespace math // good: exporting namespace
{
	[[nodiscard]] inline double f(double x) { return std::sin(x); }
	[[nodiscard]] inline double g(double x) { return std::cos(x); }
	[[nodiscard]] inline double h(double x) { return std::tan(x); }

} // namespace math

export template < typename F, typename ... Types > 
[[nodiscard]] inline constexpr auto invoke(F && f, Types && ... args) 
{ 
	return f(std::forward < Types > (args)...); 
}