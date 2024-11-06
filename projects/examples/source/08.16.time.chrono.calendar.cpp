#include <cassert>
#include <chrono>
#include <iostream>

using namespace std::literals;

int main()
{
	std::chrono::hh_mm_ss time(10h + 20min + 30s);

	std::cout << time << std::endl;

	assert(time.hours() == 10h && time.minutes() == 20min && time.seconds() == 30s);

	std::cout << time.to_duration() << std::endl;

//  ================================================================================================

	std::chrono::year_month_day date(1970y, std::chrono::January, 1d);

	std::cout << date << std::endl;

	std::cout << std::chrono::sys_days(date) << std::endl;

	assert(!(std::chrono::year(1970) / 1 / 32).ok());

//  ================================================================================================

	auto now = std::chrono::floor < std::chrono::hours > (std::chrono::system_clock::now());

	auto delta = now - std::chrono::sys_days(std::chrono::year(1970) / 1 / 1);

	std::cout << std::chrono::floor < std::chrono::days > (delta) << std::endl;

//  ================================================================================================

	std::cout << std::chrono::year_month_weekday(date).weekday() << std::endl;

//  ================================================================================================

	std::cout << now << std::endl;

	std::cout << std::chrono::zoned_time("Europe/London", now) << std::endl;
	std::cout << std::chrono::zoned_time("Europe/Berlin", now) << std::endl;
	std::cout << std::chrono::zoned_time("Europe/Moscow", now) << std::endl;
}