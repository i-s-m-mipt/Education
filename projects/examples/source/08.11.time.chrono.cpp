#include <cassert>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>

//  ================================================================================================

template < typename C > void verify(const std::string & name)
{
	std::cout << name << " : ";
	
	std::cout << std::setprecision(9) << std::fixed << 1.0 * C::period::num / C::period::den;
		
	if (C::is_steady) std::cout << " / steady";

	std::cout << std::endl;
}

//  ================================================================================================

class Chronometer // support: RAII
{
public:

	using clock_t = std::chrono::steady_clock;

	explicit Chronometer(std::string name) : m_name(std::move(name)), m_begin(clock_t::now())
	{
		std::cout << "Chronometer " << m_name << " launched ... " << std::endl;
	}

   ~Chronometer() noexcept 
	{
		try { elapsed(); } catch (...) { std::abort(); }
	}

	void elapsed() const
	{
		const auto duration = clock_t::now() - m_begin;

		const auto delta = std::chrono::duration_cast < std::chrono::microseconds > (duration);

		std::cout << "Chronometer " << m_name << " elapsed ";

		std::cout << std::setprecision(6) << std::fixed << delta.count() / 1'000'000.0;

		std::cout << " (seconds)" << std::endl;
	}

private:

	const std::string m_name;

	const clock_t::time_point m_begin;

}; // class Chronometer

//  ================================================================================================

int main()
{
	verify < std::chrono::system_clock > ("system clock");
	verify < std::chrono::steady_clock > ("steady clock");

//  ================================================================================================
	
	std::cout << std::chrono::system_clock::time_point() << std::endl;

	auto now = std::chrono::system_clock::now();

	std::cout << now << ' ' << std::chrono::system_clock::to_time_t(now) << std::endl; // support: 2038

//  ================================================================================================

	constexpr std::chrono::duration < long long, std::ratio < 1, 1000 > > duration_1(42);

	constexpr std::chrono::milliseconds duration_2(42);

	constexpr auto result = std::chrono::hours(100) + std::chrono::minutes(200);

	std::cout << result.count() << std::endl;

	std::cout << std::chrono::seconds(result) << std::endl;

	std::cout << std::chrono::duration_cast < std::chrono::days > (result) << std::endl;

	std::cout << now - std::chrono::days(10) << std::endl;

	std::cout << now - std::chrono::system_clock::time_point() << std::endl;

//  ================================================================================================

	constexpr std::size_t size = 1'000'000;

	constexpr auto epsilon = 0.000001;

	{
		Chronometer chronometer("test"); // support: Google.Benchmark

		auto test = 0.0;

		for (std::size_t i = 0; i < size; ++i)
		{
			auto l = std::pow(std::sin(i), 2.0);
			auto r = std::pow(std::cos(i), 2.0);

			test += (l + r);
		}

		assert(std::abs(test - 1'000'000.0) < epsilon);
	}

//  ================================================================================================

	{
		boost::timer::cpu_timer timer; // support: Google.Benchmark

		auto test = 0.0;

		for (std::size_t i = 0; i < size; ++i)
		{
			auto l = std::pow(std::sin(i), 2.0);
			auto r = std::pow(std::cos(i), 2.0);

			test += (l + r);
		}

		assert(std::abs(test - 1'000'000.0) < epsilon);

		std::cout << timer.format() << std::endl;
	}

	return 0;
}