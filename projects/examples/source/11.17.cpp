///////////////////////////////////////////////////////////////

#include <algorithm>
#include <print>
#include <random>
#include <vector>

///////////////////////////////////////////////////////////////

void show(std::vector < int > const & vector)
{
	std::print("show : vector = {{ ");

	for (auto element : vector)
	{
		std::print("{} ", element);
	}

	std::print("}}\n"); 
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