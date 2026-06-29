////////////////////////////////////////////////////////////////

// chapter : Characters

////////////////////////////////////////////////////////////////

// content : Functions std::stod and std::to_string
//
// content : Functions std::to_chars and std::from_chars
//
// content : Enumeration std::chars_format

////////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <cmath>
#include <charconv>
#include <iterator>

////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////

int main()
{
    assert(equal(std::stod(std::to_string(1.0)), 1.0));

//  ------------------------------------------------------------

    std::array < char, 1 << 10 > array = {};

//  ------------------------------------------------------------

    auto begin = std::begin(array), end = std::end(array);

//  ------------------------------------------------------------

    std::to_chars(begin, end, 1.0, std::chars_format::fixed, 1);

//  ------------------------------------------------------------

    assert(array.at(0) == '1');

    assert(array.at(1) == '.');

    assert(array.at(2) == '0');

//  ------------------------------------------------------------

    auto x = 0.0;

//  ------------------------------------------------------------

    std::from_chars(begin, end, x);

//  ------------------------------------------------------------

    assert(equal(x, 1.0));
}

////////////////////////////////////////////////////////////////