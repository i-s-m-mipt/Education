#include <cassert>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>

//  ================================================================================================

template < typename C > void print(const std::string & name)
{
	std::cout << name << " : tick = ";
	
	std::cout << std::setprecision(9) << std::fixed << 1.0 * C::period::num / C::period::den;
		
	if (C::is_steady) 
	{
		std::cout << " / steady";
	}

	std::cout << '\n';
}

//  ================================================================================================

class Chronometer
{
public:

	using clock_t = std::chrono::steady_clock;

//  ------------------------------------------------------------------------------------------------

	explicit Chronometer(const std::string & name) : m_name(name), m_begin(clock_t::now())
	{
		std::cout << "Chronometer " << m_name << " launched ... \n";
	}

   ~Chronometer() 
	{
		elapsed();
	}

//  ------------------------------------------------------------------------------------------------

	void elapsed() const
	{
		auto duration = clock_t::now() - m_begin;

		auto delta = std::chrono::duration_cast < std::chrono::microseconds > (duration);

		std::cout << "Chronometer " << m_name << " elapsed ";

		std::cout << std::setprecision(6) << std::fixed << delta.count() / 1'000'000.0;

		std::cout << " (seconds)\n";
	}

private:

	const std::string m_name; clock_t::time_point m_begin;
};

//  ================================================================================================

[[nodiscard]] auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

//  ================================================================================================

int main()
{
	print < std::chrono::system_clock > ("system");
	print < std::chrono::steady_clock > ("steady");

//  ------------------------------------------------------------------------------------------------
	
	std::cout << std::chrono::system_clock::time_point() << std::endl;

	auto now = std::chrono::system_clock::now();

	std::cout << now << ' ' << std::chrono::system_clock::to_time_t(now) << std::endl;

//  ------------------------------------------------------------------------------------------------

	std::chrono::duration < long long, std::ratio < 1, 1000 > > duration_1(42);

	std::chrono::milliseconds duration_2(42);

	auto duration_3 = std::chrono::hours(100) + std::chrono::minutes(200);

	std::cout << duration_3.count() << std::endl;

	std::cout << std::chrono::seconds(duration_3) << std::endl;

	std::cout << std::chrono::duration_cast < std::chrono::days > (duration_3) << std::endl;

	std::cout << now - std::chrono::days(10) << std::endl;

	std::cout << now - std::chrono::system_clock::time_point() << std::endl;

//  ------------------------------------------------------------------------------------------------

	auto size = 1'000'000uz;

//  ------------------------------------------------------------------------------------------------

	{
		Chronometer chronometer("test"); // support: Google.Benchmark

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

//  ================================================================================================

	boost::timer::cpu_timer timer; // support: Google.Benchmark

	auto result = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		result += 
		(
			std::pow(std::sin(i), 2.0) +
			std::pow(std::cos(i), 2.0)
		);
	}

	assert(equal(result, size));

	std::cout << "timer :" << timer.format() << '\n';
}