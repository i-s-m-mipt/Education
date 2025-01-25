#include <cassert>
#include <cstdint>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////

enum class State : std::uint8_t 
{ 
	slow = 0, fast = 1, size 
};

//////////////////////////////////////////////////////////////////////////////

//  enum State { slow, fast }; // bad

//////////////////////////////////////////////////////////////////////////////

int main()
{
	{	
		std::cout << "main : enter int : "; auto state = 0; std::cin >> state;

		if (state > 0 && state < static_cast < int > (State::size)) 
		{
			std::cout << "main : selection : ";

			switch (State(state))
			{
				case State::slow: { std::cout << "(1)\n"; break; }
				
				case State::fast: { std::cout << "(2)\n"; break; }

				default:
				{
					std::cout << "(3)\n"; break;
				}
			}
		}
	}
}