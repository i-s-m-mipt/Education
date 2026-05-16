/////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Arithmetic

/////////////////////////////////////////////////////////////////////////////////////////////

// content : Timing

/////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <print>

/////////////////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer(char const * scope) : m_scope(scope), m_begin(std::chrono::steady_clock::now()) {}

//  -----------------------------------------------------------------------------------------

   ~Timer()
	{
		std::print("{} : {:.6f}\n", m_scope, elapsed().count());
	}

//  -----------------------------------------------------------------------------------------

	auto elapsed() const
	{
		return std::chrono::duration_cast < D > (std::chrono::steady_clock::now() - m_begin);
	}

private :

	char const * m_scope = nullptr;

	std::chrono::steady_clock::time_point m_begin;
};

/////////////////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
	}

	return x;
}

/////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Timer timer("main : timer");

//  -------------------------------------------

	assert(equal(calculate(1 << 20), 1 << 20));
}

/////////////////////////////////////////////////////////////////////////////////////////////