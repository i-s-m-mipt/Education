#include <iostream>

enum class Color
{
	R, G, B, quantity,

}; // enum class Color

void f(Color c)
{
	switch (c)
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

using underlying_t = char;

enum class Message : underlying_t // note: more compact
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
	using integer_t = unsigned int;

	std::cout << "Enter color number: "; integer_t c{};

	if (std::cin >> c; c < static_cast < integer_t > (Color::quantity))
	{
		f(static_cast < Color > (c));
	}

	State s_1 = alpha;
	State s_2 = gamma;

	g(s_1 | s_2);
	
	return 0;
}