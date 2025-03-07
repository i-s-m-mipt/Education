#include <cassert>
#include <chrono>
#include <iostream>
#include <ratio>

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::chrono::duration < int, std::ratio < 1, 1'000 > > duration_1(1'000);

//  --------------------------------------------------------------------------------------

	std::chrono::milliseconds duration_2(1'000);

//  --------------------------------------------------------------------------------------

	assert(std::chrono::microseconds(duration_1).count() == 1'000'000);

//  --------------------------------------------------------------------------------------

	assert(std::chrono::duration_cast < std::chrono::seconds > (duration_1).count() == 1);

//  --------------------------------------------------------------------------------------

	assert(duration_1 + duration_2 == std::chrono::milliseconds(2'000));
}