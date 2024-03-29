#include <cassert>
#include <cstdint>
#include <iostream>

enum class Color { R, G, B, quantity }; // good: quantity as limit

void f(Color c)
{
	switch (c) // good: enumerators provide readability
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

using underlying_t = std::uint16_t;

enum class Message : underlying_t { empty, debug, error, fatal }; // note: less size

enum State : underlying_t
{
	alpha = 0x01,
	betta = 0x02,
	gamma = 0x04,
	delta = 0x08

}; // enum State : underlying_t

inline constexpr void g(underlying_t s) noexcept { assert(s & delta || s & gamma); }

int main()
{
	std::cout << "Enter color number: "; unsigned int c{};

	if (std::cin >> c; c < static_cast < unsigned int > (Color::quantity))
	{
		f(static_cast < Color > (c));
	}

	constexpr State s_1 = alpha;
	constexpr State s_2 = gamma;

	g(s_1 | s_2); // good: one argument instead many flags
	
	return 0;
}