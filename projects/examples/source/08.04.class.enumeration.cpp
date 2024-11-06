#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

//  ================================================================================================

enum class Color : std::uint8_t 
{ 
	R, G, B, quantity 
};

//  ================================================================================================

void test(Color color)
{
	switch (color)
	{
		case Color::R: { std::clog << "(1)"; break; }
		case Color::G: { std::clog << "(2)"; break; }
		case Color::B: { std::clog << "(3)"; break; }

		default:
		{
			std::clog << "(4)"; break;
		}
	}

	std::clog << '\n';
}

//  ================================================================================================

enum State : std::uint8_t
{
	fast = 0x01,
	slow = 0x02,
};

//  ================================================================================================

int main()
{
	std::cout << "Enter 1 unsigned integer : "; unsigned int color; std::cin >> color;

	if (color < static_cast < unsigned int > (Color::quantity)) 
	{
		test(static_cast < Color > (color));
	}

//  ------------------------------------------------------------------------------------------------

	auto state = fast | slow;

	[[maybe_unused]] auto is_fast = static_cast < bool > (state & fast);
	[[maybe_unused]] auto is_slow = static_cast < bool > (state & slow);
}