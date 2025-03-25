#include <iostream>

////////////////////////////////////////////////////////////

int main()
{
    for (auto i = 0uz; i < 5; ++i)
	{
		std::cout << "main : iteration : i = " << i << '\n';
			
		continue; // support : compiler-explorer.com

		std::cout << "main : iteration : i = " << i << '\n';
	}
}