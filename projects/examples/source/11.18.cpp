//////////////////////////////////////////////////////////////////

// chapter : Ranges

//////////////////////////////////////////////////////////////////

// content : Algorithms
//
// content : Unique Random Number Generation Algorithm
//
// content : Algorithms std::ranges::iota and std::ranges::shuffle

//////////////////////////////////////////////////////////////////

#include <algorithm>
#include <print>
#include <random>
#include <vector>

//////////////////////////////////////////////////////////////////

void show(std::vector < int > const & vector)
{
	std::print("show : vector = {{ ");

	for (auto element : vector)
	{
		std::print("{} ", element);
	}

	std::print("}}\n");
}

//////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(5, 0);

//  -----------------------------------------------------------

	std::ranges::iota(vector, 1);

//  -----------------------------------------------------------

	std::ranges::shuffle(vector, std::default_random_engine());

//  -----------------------------------------------------------

	show(vector);
}

//////////////////////////////////////////////////////////////////