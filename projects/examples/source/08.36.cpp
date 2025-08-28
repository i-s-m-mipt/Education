//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////////

class Timer
{
public :

	using clock_t = std::chrono::steady_clock;

//  --------------------------------------------------------------------------------------

	Timer(std::string const & scope) : m_scope(scope), m_begin(clock_t::now()) {}

//  --------------------------------------------------------------------------------------

   ~Timer() 
	{
		std::cout << m_scope << " : timer : " << format() << " (seconds)\n";
	}

//  --------------------------------------------------------------------------------------

	auto format() const -> std::string
	{
		auto delta_1 = clock_t::now() - m_begin;

		auto delta_2 = std::chrono::duration_cast < std::chrono::microseconds > (delta_1);

		return std::format("{:.6f}", 1.0 * delta_2.count() / 1'000'000);
	}

private :

	std::string m_scope;
	
	clock_t::time_point m_begin;
};

//////////////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

//////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Timer timer("main");

//  -----------------------------------------------

	assert(equal(calculate(1'000'000), 1'000'000));
}

//////////////////////////////////////////////////////////////////////////////////////////