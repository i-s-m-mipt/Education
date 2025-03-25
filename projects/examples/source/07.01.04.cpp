#include <cstdint>
#include <iostream>

///////////////////////////////////////////////////////////////

enum class State : std::uint8_t 
{ 
	slow = 0, fast = 1, size 
};

///////////////////////////////////////////////////////////////

//  enum State { slow, fast }; // bad

///////////////////////////////////////////////////////////////

int main()
{
	auto x = 0;

//  -----------------------------------------------------------
	
	std::cout << "main : enter int : "; std::cin >> x;

	std::cout << "main : selection : ";

//  -----------------------------------------------------------

	if (x > 0 && x < static_cast < int > (State::size)) 
	{
		switch (State(x))
		{
			case State::slow : { std::cout << "(1)\n"; break; }
				
			case State::fast : { std::cout << "(2)\n"; break; }

			default :
			{
				std::cout << "(3)\n"; break;
			}
		}
	}
}