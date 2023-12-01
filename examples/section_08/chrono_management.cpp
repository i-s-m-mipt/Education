#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

template < typename C > void verify(const std::string & name)
{
	std::cout << name << " : ";
	
	std::cout << std::setprecision(9) << std::fixed << 1.0 * C::period::num / C::period::den;
		
	if (C::is_steady) std::cout << " / steady";

	std::cout << std::endl;
}

struct kilometers // note: user-defined units
{ 
	unsigned long long n; 

}; // struct kilometers

constexpr auto operator""_km(unsigned long long km)
{
	return kilometers{ km };
}

class Timer
{
public:

	using clock_t = std::chrono::steady_clock;

	explicit Timer(std::string name) : m_name(std::move(name)), m_begin(clock_t::now())
	{
		std::cout << "Timer " << m_name << " launched ... " << std::endl;
	}

	~Timer() { elapsed(); }

	void elapsed() const
	{
		std::cout << "Timer " << m_name << " elapsed " << std::setprecision(6) << std::fixed <<
			static_cast < double > (std::chrono::duration_cast < std::chrono::microseconds >
				(clock_t::now() - m_begin).count()) / 1'000'000.0 << " (seconds)" << std::endl;
	}

private:

	const std::string m_name;

	const clock_t::time_point m_begin;

}; // class Timer

int main()
{
	verify < std::chrono::system_clock > ("system clock");
	verify < std::chrono::steady_clock > ("steady clock");
	
	std::cout << std::chrono::system_clock::time_point() << std::endl; // note: clock epoch

	auto now = std::chrono::system_clock::now(); // note: time point for current time

	std::cout << now << ' ' << std::chrono::system_clock::to_time_t(now) << std::endl;

	[[maybe_unused]] std::chrono::duration < long long, std::ratio < 1, 1000 > > duration_1(42);

	[[maybe_unused]] std::chrono::milliseconds duration_2(42);

	using namespace std::literals;

	[[maybe_unused]] auto duration_3 = 42ms; // note: standard literal

	[[maybe_unused]] auto distance = 88_km; // note: user-defined literal

	auto result = std::chrono::hours(100) + std::chrono::minutes(200);

	std::cout << result.count() << std::endl;

	std::cout << std::chrono::seconds(result) << std::endl;

	std::cout << std::chrono::duration_cast <std::chrono::days > (result) << std::endl;

	{
		Timer timer("test");

		const std::size_t size = 1000; // note: measured operations

		auto test = 0.0;

		for (std::size_t i = 0; i < size; ++i)
		{
			for (std::size_t j = 0; j < size; ++j)
			{
				auto argument = 1.0 * i / size;

				auto l = std::pow(std::sin(argument), 2.0);
				auto r = std::pow(std::cos(argument), 2.0);

				test += (l + r); // note: required optimization
			}
		}

		std::cout << "test = " << std::defaultfloat << test << std::endl;
	}

	return 0;
}