///////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

///////////////////////////////////////////////////////////////////////

// content : Statements if constexpr and if consteval
//
// content : Functions std::max and std::min

///////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <print>

///////////////////////////////////////////////////////////////////////

void show(auto x, auto ... xs) // support : https://cppinsights.io
{
	std::print("show : x = {} sizeof...(xs) = {}\n", x, sizeof...(xs));

	if constexpr (sizeof...(xs) > 0)
	{
		show(xs...);
	}
}

///////////////////////////////////////////////////////////////////////

constexpr auto test(int x, int y)
{
	if consteval
	{
		return std::max(x, y);
	}
	else
	{
		return std::min(x, y);
	}
}

///////////////////////////////////////////////////////////////////////

int main()
{
	show(1, 2.0, "aaaaa");

//  -------------------------------

    auto x = 1, y = 2;

//  -------------------------------

	 		  auto z1 = test(x, y);

	constexpr auto z2 = test(1, 2);

//  -------------------------------

	assert(z1 == 1);

	assert(z2 == 2);
}

///////////////////////////////////////////////////////////////////////