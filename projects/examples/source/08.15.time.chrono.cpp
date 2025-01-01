#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <format>
#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	std::intmax_t N, 
	std::intmax_t D 
> 
auto & operator<<(std::ostream & stream, const std::ratio < N, D > & ratio)
{
	return stream << ratio.num << '/' << ratio.den << " (seconds)";
}

/////////////////////////////////////////////////////////////////////////////////////////////

class Chronometer
{
public:

	using clock_t = std::chrono::steady_clock;

//  --------------------------------------------------------------------------------------

	Chronometer(const std::string & scope) : m_scope(scope), m_begin(clock_t::now()) {}

   ~Chronometer() 
	{
		elapsed();
	}

//  --------------------------------------------------------------------------------------

	void elapsed() const
	{
		auto duration = clock_t::now() - m_begin;

		auto delta = std::chrono::duration_cast < std::chrono::microseconds > (duration);

		std::cout << m_scope << " : chronometer : ";

		std::cout << std::format("{:.6f}", delta.count() / 1'000'000.0) << " (seconds)\n";
	}

private:

	const std::string m_scope; clock_t::time_point m_begin;
};

/////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	assert(!std::chrono::system_clock::is_steady);

	auto system_clock_period = std::chrono::system_clock::period();
	
	std::cout << "main : system_clock_period = " << system_clock_period << '\n';

//  ------------------------------------------------------------------------
	
	auto epoch = std::chrono::system_clock::time_point();

	std::cout << "main : epoch = " << epoch << '\n';

	auto local = std::chrono::system_clock::now();
	
	std::cout << "main : local = " << local << '\n';

	assert(std::chrono::system_clock::to_time_t(local) == time(nullptr));

//  ------------------------------------------------------------------------

	std::chrono::duration < int, std::ratio < 1, 1'000 > > duration_1(1'000);

	std::chrono::milliseconds duration_2(1'000);

	auto duration_3 = std::chrono::hours(1) + std::chrono::minutes(1);

	assert(duration_3.count() == 61);

	assert(std::chrono::seconds(duration_3).count() == 3'660);

	auto delta = std::chrono::floor < std::chrono::days > (local - epoch);

	std::cout << "main : delta = " << delta.count() << " (days)\n";

//  ------------------------------------------------------------------------

	auto size = 1'000'000uz;

//  ------------------------------------------------------------------------

	{
		Chronometer chronometer("main");

		auto result = 0.0;

		for (auto i = 0uz; i < size; ++i)
		{
			result += 
			(
				std::pow(std::sin(1.0 * i), 2.0) +
				std::pow(std::cos(1.0 * i), 2.0)
			);
		}

		assert(equal(result, static_cast < double > (size)));
	}

//  ------------------------------------------------------------------------

	boost::timer::cpu_timer cpu_timer;

	auto result = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		result += 
		(
			std::pow(std::sin(1.0 * i), 2.0) +
			std::pow(std::cos(1.0 * i), 2.0)
		);
	}

	assert(equal(result, size));

	std::cout << "main : cpu_timer :" << cpu_timer.format();
}