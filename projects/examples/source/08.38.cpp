//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////////

#include <boost/timer/timer.hpp>

//////////////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer(std::string const & scope) : m_scope(scope) {}

//  --------------------------------------------------------------------------------------

   ~Timer() 
	{
		std::cout << m_scope << " : " << std::format("{:.6f}", elapsed().count()) << '\n';
	}

//  --------------------------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (duration_t(m_timer.elapsed().wall));
	}

private :

	using duration_t = std::chrono::nanoseconds;

//  --------------------------------------------------------------------------------------

	std::string m_scope;
	
	boost::timer::cpu_timer m_timer;
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
    Timer timer("main : timer");

//  -----------------------------------------------

	assert(equal(calculate(1'000'000), 1'000'000));
}

//////////////////////////////////////////////////////////////////////////////////////////