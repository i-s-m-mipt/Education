//////////////////////////////////////////////////////////////////////////////

// chapter : Debugging and Profiling Tools

//////////////////////////////////////////////////////////////////////////////

// content : Scoped Enumerations
//
// content : Declaration enum class
//
// content : Expected Undefined Behavior
//
// content : Function std::unreachable
//
// content : Underlying Types
//
// content : Type Alias std::uint8_t
//
// content : Function std::to_underlying
//
// content : Unscoped Enumerations
//
// content : Declaration enum

//////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdint>
#include <iostream>
#include <print>
#include <utility>

//////////////////////////////////////////////////////////////////////////////

enum class State_v1 : std::uint8_t
{
	slow = 0, fast = 1, size
};

//////////////////////////////////////////////////////////////////////////////

// enum State_v2 : std::uint8_t // bad
// {
//     slow = 0, fast = 1, size
// };

//////////////////////////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  --------------------------------------------------------------------------

	std::print("main : enter int x : "); std::cin >> x;

//  --------------------------------------------------------------------------

//	State_v1 state_v1_1 = x; // error

//  --------------------------------------------------------------------------

	auto state_v1_2 = static_cast < State_v1 > (x);

//  --------------------------------------------------------------------------

	switch (state_v1_2)
	{
		case State_v1::slow : { std::print("main : selection (1)\n"); break; }

		case State_v1::fast : { std::print("main : selection (2)\n"); break; }

	//  ----------------------------------------------------------------------

		default :
		{
			std::unreachable();
		}
	}

//  --------------------------------------------------------------------------

//	assert(state_v1_2 == x); // error

//  --------------------------------------------------------------------------

	assert(std::to_underlying(state_v1_2) == x);
}

//////////////////////////////////////////////////////////////////////////////