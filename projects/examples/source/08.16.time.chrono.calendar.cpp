#include <cassert>
#include <chrono>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto local = std::chrono::system_clock::now();

		auto time_point = std::chrono::floor < std::chrono::days > (local);

		auto duration = std::chrono::floor < std::chrono::seconds > (local) - time_point;

		std::chrono::hh_mm_ss hh_mm_ss(duration);

		std::cout << "main : hh_mm_ss = " << hh_mm_ss << '\n';

		assert(hh_mm_ss.to_duration() == duration);
	}

//  -------------------------------------------------------------------------------------

	{
		auto local = std::chrono::system_clock::now();

		auto time_point = std::chrono::floor < std::chrono::days > (local);

		std::chrono::year_month_day year_month_day(time_point);

		std::cout << "main : year_month_day = " << year_month_day << '\n';

		assert(std::chrono::sys_days(year_month_day) == time_point);
	}

//  -------------------------------------------------------------------------------------

	{
		auto local = std::chrono::system_clock::now();

		auto time_point = std::chrono::floor < std::chrono::days > (local);

		auto weekday = std::chrono::year_month_weekday(time_point).weekday();

		std::cout << "main : weekday = " << weekday << '\n';
	}

//  -------------------------------------------------------------------------------------

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