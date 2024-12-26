#include <cassert>
#include <chrono>
#include <iostream>

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto local = std::chrono::floor < std::chrono::seconds > (std::chrono::system_clock::now());

//  --------------------------------------------------------------------------------------------

	auto duration = local - std::chrono::floor < std::chrono::days > (local);

	std::chrono::hh_mm_ss hh_mm_ss(duration);

	std::cout << "main : hh_mm_ss = " << hh_mm_ss << '\n';

	assert(hh_mm_ss.to_duration() == duration);

//  --------------------------------------------------------------------------------------------

	auto time_point = std::chrono::floor < std::chrono::days > (local);

	std::chrono::year_month_day year_month_day(time_point);

	std::cout << "main : year_month_day = " << year_month_day << '\n';

	assert(std::chrono::sys_days(year_month_day) == time_point);

//  --------------------------------------------------------------------------------------------

	auto weekday = std::chrono::year_month_weekday(year_month_day).weekday();

	std::cout << "main : weekday = " << weekday << '\n';

//  --------------------------------------------------------------------------------------------

	std::cout << "main : local (GMT) = " << std::chrono::zoned_time("Europe/London", local) << '\n';
	std::cout << "main : local (CET) = " << std::chrono::zoned_time("Europe/Berlin", local) << '\n';
	std::cout << "main : local (MSK) = " << std::chrono::zoned_time("Europe/Moscow", local) << '\n';
}