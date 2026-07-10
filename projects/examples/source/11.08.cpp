///////////////////////////////////////////////////////////////

// chapter : Programming with Algorithms

///////////////////////////////////////////////////////////////

// content : Type Erasure
//
// content : Wrapper std::function
//
// content : Event-Driven Programming
//
// content : Slots and Signals
//
// content : Library Boost.Signals2

///////////////////////////////////////////////////////////////

// support : https://www.qt.io

///////////////////////////////////////////////////////////////

#include <functional>
#include <print>
#include <vector>

///////////////////////////////////////////////////////////////

#include <boost/signals2.hpp>

///////////////////////////////////////////////////////////////

int main()
{
    std::vector < std::function < int(int, int) > > functions =
	{
		[](auto x, auto y) static { return x + y; },

		[](auto x, auto y) static { return x - y; },

		[](auto x, auto y) static { return x * y; },

		[](auto x, auto y) static { return x / y; }
	};

//  -----------------------------------------------------------

	boost::signals2::signal < void() > signal;

//  -----------------------------------------------------------

	auto lambda_1 = []() static { std::print("lambda_1\n"); };

	auto lambda_2 = []() static { std::print("lambda_2\n"); };

//  -----------------------------------------------------------

	signal.connect(lambda_1);

	signal.connect(lambda_2);

//  -----------------------------------------------------------

	signal();
}

///////////////////////////////////////////////////////////////