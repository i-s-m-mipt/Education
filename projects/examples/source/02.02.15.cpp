#include <iostream>

//////////////////////////////////////////////////////////////

int main()
{
    char x = 0;

	do
	{
		std::cout << "main : iteration : ";

		std::cout << "enter \'b\' to break : "; std::cin >> x;
	} 
	while (x != 'b');
}