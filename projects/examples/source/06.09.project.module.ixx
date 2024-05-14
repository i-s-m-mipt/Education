module;

#include <cmath>

export module math;

export import math.submodule;

//  ================================================================================================

export void hello_module();

//  ================================================================================================

export namespace math
{
	[[nodiscard]] inline double f(double x) { return std::sin(x); }
	[[nodiscard]] inline double g(double x) { return std::cos(x); }
	[[nodiscard]] inline double h(double x) { return std::tan(x); }

} // namespace math

//  ================================================================================================

export template < typename F, typename ... Ts > 

[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Ts && ... args) 
{ 
	return f(std::forward < Ts > (args)...); // support: std::invoke
}