#include <cstdint>
#include <iostream>

enum class Color
{
	red, green, blue, quantity,
};

void f(Color c)
{
	switch (c)
	{
	[[likely]] case Color::red:
	{
		std::cout << "red" << std::endl; 
		break;
	}
	case Color::green:
	{
		std::cout << "green" << std::endl;
		break;
	}
	case Color::blue:
	{
		std::cout << "blue" << std::endl;
		break;
	}
	[[unlikely]] default:
	{
		std::cout << "default" << std::endl;
		break;
	}
	}
}

using underlying_t = std::uint8_t;

enum class Message : underlying_t
{
	empty, debug, error, fatal,
};

enum State : underlying_t
{
	alpha = 0x01,
	betta = 0x02,
	gamma = 0x04,
	delta = 0x08,
};

void g(underlying_t s)
{
	if (s & delta || s & gamma)
	{
		std::cout << "gamma+" << std::endl;
	}
}

enum
{
	up = 1,
	down,
	left,
	right,
};

int main()
{
	using integer_t = unsigned int;

	integer_t c = 0;

	if (std::cin >> c; c < static_cast < integer_t > (Color::quantity))
	{
		f(static_cast < Color > (c));
	}

	State s_1 = alpha;
	State s_2 = gamma;

	g(s_1 | s_2);
	
	return 0;
}