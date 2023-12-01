#include <cstdint>
#include <iostream>

enum class Color
{
	R, G, B, quantity, // good: quantity as limit

}; // enum class Color

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

enum class Message : underlying_t // note: less size
{
	empty, debug, error, fatal,

}; // enum class Message : underlying_t

enum State : underlying_t
{
	alpha = 0x01,
	betta = 0x02,
	gamma = 0x04,
	delta = 0x08,

}; // enum State : underlying_t

void g(underlying_t s)
{
	if (s & delta || s & gamma) std::cout << "gamma+" << std::endl;
}

int main()
{
	std::cout << "Enter color number: "; unsigned int c{};

	if (std::cin >> c; c < static_cast < unsigned int > (Color::quantity))
	{
		f(static_cast < Color > (c));
	}

	State s_1 = alpha;
	State s_2 = gamma;

	g(s_1 | s_2);
	
	return 0;
}