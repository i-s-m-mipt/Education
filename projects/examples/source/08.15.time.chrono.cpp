#include <cassert>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////

class Chronometer
{
public:

	using clock_t = std::chrono::steady_clock;

//  --------------------------------------------------------------------------------------

	explicit Chronometer(const std::string & name) : m_name(name), m_begin(clock_t::now())
	{
		std::cout << "Chronometer " << std::quoted(m_name) << " started ... \n";
	}

   ~Chronometer() 
	{
		elapsed();
	}

//  --------------------------------------------------------------------------------------

	void elapsed() const
	{
		auto duration = clock_t::now() - m_begin;

		auto delta = std::chrono::duration_cast < std::chrono::microseconds > (duration);

		std::cout << "Chronometer " << std::quoted(m_name) << " elapsed ";

		std::cout << std::setprecision(6) << std::fixed << delta.count() / 1'000'000.0;

		std::cout << " (seconds)\n";
	}

private:

	const std::string m_name; clock_t::time_point m_begin;
};

/////////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "system clock : tick = ";
	
	std::cout << std::chrono::system_clock::period::num << '/';
	
	std::cout << std::chrono::system_clock::period::den << " (seconds)\n";

	assert(!std::chrono::system_clock::is_steady);

//  ------------------------------------------------------------------------
	
	auto epoch = std::chrono::system_clock::time_point();

	std::cout << "epoch = " << epoch << '\n';

	auto local = std::chrono::system_clock::now();
	
	std::cout << "local = " << local << '\n';

	assert(std::chrono::system_clock::to_time_t(local) == time(nullptr));

//  ------------------------------------------------------------------------

	std::chrono::duration < int, std::ratio < 1, 1000 > > duration_1(1'000);

	std::chrono::milliseconds duration_2(1'000);

	auto duration_3 = std::chrono::hours(1) + std::chrono::minutes(1);

	assert(duration_3.count() == 61);

	assert(std::chrono::seconds(duration_3).count() == 3'660);

	auto delta = std::chrono::floor < std::chrono::days > (local - epoch);

	std::cout << "delta = " << delta.count() << " (days)\n";

//  ------------------------------------------------------------------------

	auto size = 1'000'000uz;

//  ------------------------------------------------------------------------

	{
		Chronometer chronometer("test");

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

	boost::timer::cpu_timer timer;

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

	std::cout << "timer :" << timer.format();
}