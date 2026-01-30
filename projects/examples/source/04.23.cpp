////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

////////////////////////////////////////////////////////////////////

// section : Constant Expressions

////////////////////////////////////////////////////////////////////

// content : Type std::tuple
//
// content : Functions std::make_tuple, std::get and std::tie
//
// content : Metafunction std::tuple_size
//
// content : Object std::ignore
//
// content : Structured Bindings

////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <string>
#include <tuple>

////////////////////////////////////////////////////////////////////

using namespace std::literals;

////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

////////////////////////////////////////////////////////////////////

int main()
{
    auto tuple = std::make_tuple(1, 2.0, "aaaaa"s);

//  ----------------------------------------------------------------

	static_assert(std::tuple_size_v < decltype(tuple) > == 3);

//  ----------------------------------------------------------------

    assert(std::get < 0 > (tuple) == 1);

//  ----------------------------------------------------------------

    auto x = 0.0;

//  ----------------------------------------------------------------

    std::tie(std::ignore, x, std::ignore) = tuple;

//  ----------------------------------------------------------------

    assert(equal(x, 2.0));

//  ----------------------------------------------------------------

    auto const & [y, z, string] = tuple; // support : cppinsights.io

//  ----------------------------------------------------------------

    assert(y == 1 && equal(z, 2.0) && string == "aaaaa");
}

////////////////////////////////////////////////////////////////////