//////////////////////////////////////////////////////////////////

// chapter : Number Processing

//////////////////////////////////////////////////////////////////

// section : Chrono Management

//////////////////////////////////////////////////////////////////

// content : Calendars
//
// content : Years, Months, Days, Hours, Minutes and Seconds

//////////////////////////////////////////////////////////////////

#include <chrono>
#include <print>

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

    std::print("main : date = {}\n", date);

    std::print("main : wday = {}\n", wday);

	std::print("main : time = {}\n", time);
}

//////////////////////////////////////////////////////////////////