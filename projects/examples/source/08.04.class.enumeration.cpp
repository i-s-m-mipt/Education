#include <cassert>
#include <cstdint>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////

enum class Color : std::uint8_t 
{ 
	R, G, B, quantity 
};

//////////////////////////////////////////////////////////////////////////////////////

void test(Color color)
{
	std::cout << "test : selection : ";

	switch (color)
	{
		case Color::R: { std::cout << "(1)"; break; }
		case Color::G: { std::cout << "(2)"; break; }
		case Color::B: { std::cout << "(3)"; break; }

		default:
		{
			std::cout << "(4)"; break;
		}
	}

	std::cout << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////

enum State : std::uint8_t
{
	fast = 0x01,
	slow = 0x02,
};

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "Enter 1 unsigned integer : "; unsigned int color; std::cin >> color;

	if (color < static_cast < unsigned int > (Color::quantity)) 
	{
		test(static_cast < Color > (color));
	}

//  ----------------------------------------------------------------------------------

	auto state = fast | slow;

	assert(static_cast < bool > (state & fast));
	assert(static_cast < bool > (state & slow));
}