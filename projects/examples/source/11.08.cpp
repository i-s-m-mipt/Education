///////////////////////////////////////////////////////////////

// chapter : Ranges

///////////////////////////////////////////////////////////////

// content : Type Erasure
//
// content : Wrapper std::function
//
// content : Event-Driven Programming
//
// content : Slots and Signals
//
// content : Library Boost.Signals

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
		[](auto x, auto y){ return x + y; },

		[](auto x, auto y){ return x - y; },

		[](auto x, auto y){ return x * y; },

		[](auto x, auto y){ return x / y; }
	};

//  -----------------------------------------------------------

	boost::signals2::signal < void() > signal;

//  -----------------------------------------------------------

	auto lambda_1 = [](){ std::print("lambda_1\n"); };

	auto lambda_2 = [](){ std::print("lambda_2\n"); };

//  -----------------------------------------------------------

	signal.connect(lambda_1);

	signal.connect(lambda_2);

//  -----------------------------------------------------------

	signal();
}

///////////////////////////////////////////////////////////////