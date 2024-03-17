module; // note: global module fragment

#include <cmath>

export module math; // note: interface unit

export import math.submodule;

export void hello_module();

export namespace math // good: exporting namesapce
{
	[[nodiscard]] auto f(double x) { return std::sin(x); }
	[[nodiscard]] auto g(double x) { return std::cos(x); }
	[[nodiscard]] auto h(double x) { return std::tan(x); }

} // namespace math

export template < typename F, typename ... Ts >
auto call(F f, Ts ... args) { return f(args...); }