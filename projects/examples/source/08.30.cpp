//////////////////////////////////////////////////////

// chapter : Number Processing

//////////////////////////////////////////////////////

// section : Chrono Management

//////////////////////////////////////////////////////

// content : Chrono Management
//
// content : Clocks
//
// content : Clock std::chrono::system_clock
//
// content : Epochs and Periods
//
// content : Unix Epoch
//
// content : Clock std::chrono::steady_clock

//////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <print>

//////////////////////////////////////////////////////

int main()
{
    std::chrono::system_clock::time_point epoch;

//  --------------------------------------------------

    std::print("main : epoch = {}\n", epoch);

//  --------------------------------------------------

    std::chrono::system_clock::period ratio;

//  --------------------------------------------------

    assert(ratio.num == 1);

	assert(ratio.den == 1'000'000'000);

//  --------------------------------------------------

    assert(std::chrono::system_clock::is_steady == 0);

    assert(std::chrono::steady_clock::is_steady == 1);
}

//////////////////////////////////////////////////////