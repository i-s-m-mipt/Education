#include <cassert>
#include <chrono>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto local = std::chrono::floor < std::chrono::days > (std::chrono::system_clock::now());

		auto delta = std::chrono::system_clock::now() - local;

		std::chrono::hh_mm_ss time(delta);

		std::cout << "main : time = " << time << '\n';

		assert(time.to_duration() == delta);
	}

//  ---------------------------------------------------------------------------------------------

	{
		auto local = std::chrono::floor < std::chrono::days > (std::chrono::system_clock::now());

		std::chrono::year_month_day date(local);

		std::cout << "main : date = " << date << '\n';

		assert(std::chrono::sys_days(date) == local);
	}

//  ---------------------------------------------------------------------------------------------

	{
		auto local = std::chrono::floor < std::chrono::days > (std::chrono::system_clock::now());

		auto weekday = std::chrono::year_month_weekday(local).weekday();

		std::cout << "main : weekday = " << weekday << '\n';
	}

//  ---------------------------------------------------------------------------------------------

	{
		auto local = std::chrono::system_clock::now();

		auto local_gmt = std::chrono::zoned_time("Europe/London", local);

		auto local_cet = std::chrono::zoned_time("Europe/Berlin", local);

		auto local_msk = std::chrono::zoned_time("Europe/Moscow", local);

		std::cout << "main : local (GMT) = " << local_gmt << '\n';

		std::cout << "main : local (CET) = " << local_cet << '\n';

		std::cout << "main : local (MSK) = " << local_msk << '\n';
	}
}