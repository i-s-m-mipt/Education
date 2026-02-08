/////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

/////////////////////////////////////////////////////////////////////////////////

// section : Chrono Management

/////////////////////////////////////////////////////////////////////////////////

// content : Time Measurements

/////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <print>
#include <string>

/////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer(std::string const & scope) : m_scope(scope), m_begin(clock_t::now()) {}

//  -----------------------------------------------------------------------------

   ~Timer()
	{
		std::print("{} : {:.6f}\n", m_scope, elapsed().count());
	}

//  -----------------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (clock_t::now() - m_begin);
	}

private :

	using clock_t = std::chrono::steady_clock;

//  -----------------------------------------------------------------------------

	std::string m_scope;

	clock_t::time_point m_begin;
};

/////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

/////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	Timer timer("main : timer");

//  -----------------------------------------------

	assert(equal(calculate(1'000'000), 1'000'000));
}

/////////////////////////////////////////////////////////////////////////////////