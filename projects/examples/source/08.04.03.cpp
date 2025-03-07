#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>

////////////////////////////////////////////////////////////////////////

int main()
{
	std::chrono::time_point < std::chrono::system_clock > epoch;

//  --------------------------------------------------------------------

	auto now = std::chrono::system_clock::now();

//  --------------------------------------------------------------------

	auto delta = std::chrono::floor < std::chrono::days > (now - epoch);

//  --------------------------------------------------------------------

	std::cout << "main : delta = " << delta.count() << " (days)\n";

//  --------------------------------------------------------------------

	assert(std::chrono::system_clock::to_time_t(now) == time(nullptr));
}