module; // note: global module fragment

#include <cmath>

export module math; // note: interface unit

export import math.submodule;

export void hello_module();

export namespace math // good: exporting namesapce
{
	[[nodiscard]] inline auto f(double x) { return std::sin(x); }
	[[nodiscard]] inline auto g(double x) { return std::cos(x); }
	[[nodiscard]] inline auto h(double x) { return std::tan(x); }

} // namespace math

export template < typename F, typename ... Types > [[nodiscard]] inline auto invoke(F && f, Types && ... args) 
{ 
	return f(std::forward < Types > (args)...); 
}