#include <cassert>
#include <chrono>
#include <iostream>

//////////////////////////////////////////////////////

int main()
{
    std::chrono::system_clock::time_point epoch;

//  --------------------------------------------------

    std::cout << "main : epoch = " << epoch << '\n';

//  --------------------------------------------------

    std::chrono::system_clock::period ratio;

//  --------------------------------------------------

    assert(ratio.num == 1);

	assert(ratio.den == 1'000'000'000);

//  --------------------------------------------------

    assert(std::chrono::system_clock::is_steady == 0);

    assert(std::chrono::steady_clock::is_steady == 1);
}