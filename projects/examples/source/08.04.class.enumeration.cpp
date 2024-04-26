#include <cassert>
#include <cstdint>
#include <iostream>

// =================================================================================================

enum class Color { R, G, B, quantity }; // good: quantity as limit

// =================================================================================================

void f(Color color)
{
	switch (color) // good: enumerators provide readability
	{
		case Color::R: { std::cout << "R"; break; }
		case Color::G: { std::cout << "G"; break; }
		case Color::B: { std::cout << "B"; break; }

		[[unlikely]] default:
		{
			std::cout << "default"; break;
		}
	}

	std::cout << std::endl;
}

// =================================================================================================

enum class Message : std::uint16_t { empty, debug, error, fatal }; // note: less size

// =================================================================================================

enum State : std::uint16_t
{
	alpha = 0x01,
	betta = 0x02,
	gamma = 0x04,
	delta = 0x08

}; // enum State : std::uint16_t

inline constexpr void g(std::uint16_t state) noexcept { assert(state & delta || state & gamma); }

// =================================================================================================

int main()
{
	std::cout << "Enter color number: "; unsigned int color{};

	if (std::cin >> color; color < static_cast < unsigned int > (Color::quantity))
	{
		f(static_cast < Color > (color));
	}

	constexpr State state_1 = alpha;
	constexpr State state_2 = gamma;

	g(state_1 | state_2); // good: one argument instead many flags
	
	return 0;
}