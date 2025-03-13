#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
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
	std::vector < int > vector(5, 0);

    std::default_random_engine engine;

//  -----------------------------------------------------------

	std::ranges::iota(vector, 1);

	std::shuffle(std::begin(vector), std::end(vector), engine);

//  -----------------------------------------------------------

	test(vector);
}