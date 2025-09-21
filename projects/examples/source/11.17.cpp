///////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

///////////////////////////////////////////////////////////////

void show(std::vector < int > const & vector)
{
	std::cout << "show : vector = { ";

	for (auto element : vector)
	{
		std::cout << element << ' ';
	}

	std::cout << "}\n";
}

///////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	std::ranges::shuffle(vector, std::default_random_engine());

//  -----------------------------------------------------------

	show(vector);
}

///////////////////////////////////////////////////////////////