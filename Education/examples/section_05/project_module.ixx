module;

#include <cmath>

export module math;

export void hello_module();

export namespace math
{
	auto f(double x) { return std::sin(x); }
	auto g(double x) { return std::cos(x); }
	auto h(double x) { return std::tan(x); }

} // namespace math

export template < typename F, typename ... Ts >
auto call(F f, Ts ... args) { return f(args...); }