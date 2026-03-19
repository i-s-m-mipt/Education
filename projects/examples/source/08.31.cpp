//////////////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

//////////////////////////////////////////////////////////////////////////////////////////

// section : Chrono Management

//////////////////////////////////////////////////////////////////////////////////////////

// content : Durations
//
// content : Type std::chrono::duration
//
// content : Compile-Time Rational Arithmetic
//
// content : Type std::ratio
//
// content : Type Aliases std::chrono::seconds and std::chrono::milliseconds 
//
// content : Duration Type Conversions
//
// content : Function std::chrono::duration_cast

//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <ratio>

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::chrono::duration < int, std::ratio < 1, 1'000 > > duration_1(1'000);

//  --------------------------------------------------------------------------------------

	std::chrono::seconds duration_2(2);

//  --------------------------------------------------------------------------------------

	assert(std::chrono::milliseconds(duration_2).count() == 2'000);

//  --------------------------------------------------------------------------------------

	assert(std::chrono::duration_cast < std::chrono::seconds > (duration_1).count() == 1);

//  --------------------------------------------------------------------------------------

	assert(duration_1 + duration_2 == std::chrono::milliseconds(3'000));
}

//////////////////////////////////////////////////////////////////////////////////////////