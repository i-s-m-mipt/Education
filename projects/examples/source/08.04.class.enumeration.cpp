#include <cassert>
#include <cstdint>
#include <iostream>

/////////////////////////////////////////////////////////////////////////

enum class Color : std::uint8_t 
{ 
	R, G, B, quantity 
};

/////////////////////////////////////////////////////////////////////////

enum State : std::uint8_t
{
	fast = 0x01, slow = 0x02,
};

/////////////////////////////////////////////////////////////////////////

int main()
{
	{	
		std::cout << "main : enter int : "; int color; std::cin >> color;

		if (color > 0 && color < static_cast < int > (Color::quantity)) 
		{
			std::cout << "main : selection : ";

			switch (Color(color))
			{
				case Color::R: { std::cout << "(1)\n"; break; }
				
				case Color::G: { std::cout << "(2)\n"; break; }

				case Color::B: { std::cout << "(3)\n"; break; }

				default:
				{
					std::cout << "(4)\n"; break;
				}
			}
		}
	}

//  ---------------------------------------------------------------------

	{
		[[maybe_unused]] auto state = fast | slow;
	}
}