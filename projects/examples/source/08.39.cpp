//////////////////////////////////////////////////////////////////

#include <chrono>
#include <iostream>

//////////////////////////////////////////////////////////////////

int main()
{
    auto now_1 = std::chrono::system_clock::now();

    auto now_2 = std::chrono::floor < std::chrono::days > (now_1);

//  --------------------------------------------------------------

    std::chrono::year_month_day date(now_2);

//  --------------------------------------------------------------

    auto wday = std::chrono::year_month_weekday(now_2).weekday();

//  --------------------------------------------------------------

	std::chrono::hh_mm_ss time(now_1 - now_2);

//  --------------------------------------------------------------

    std::cout << "main : date = " << date << '\n';

    std::cout << "main : wday = " << wday << '\n';

	std::cout << "main : time = " << time << '\n';
}

//////////////////////////////////////////////////////////////////