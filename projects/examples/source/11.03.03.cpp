#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

///////////////////////////////////////////////////////////////

void test(const std::vector < int > & vector)
{
	std::cout << "test : vector = { ";

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

	test(vector);
}