#include <cassert>
#include <cstdint>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////

enum class Color : std::uint8_t 
{ 
	R, G, B, quantity 
};

//////////////////////////////////////////////////////////////////////////////////////

enum State : std::uint8_t
{
	fast = 0x01,
	slow = 0x02,
};

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::cout << "main : enter 1 unsigned integer : "; unsigned int color; std::cin >> color;

	if (color < static_cast < unsigned int > (Color::quantity)) 
	{
		std::cout << "main : selection : ";

		switch (Color(color))
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

//  ----------------------------------------------------------------------------------

	auto state = fast | slow;

	assert(static_cast < bool > (state & fast));
	assert(static_cast < bool > (state & slow));
}