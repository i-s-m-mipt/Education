#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

////////////////////////////////////////////////////////////////////////

void test(const std::vector < int > & vector)
{
	std::cout << "test : vector = { ";

	for (auto element : vector)
	{
		std::cout << element << ' ';
	}

	std::cout << "}\n";
}

////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(5, 0);

	std::uniform_int_distribution distribution(1, 5);

	std::default_random_engine engine;

//  --------------------------------------------------------------------

	std::generate
	(
		std::begin(vector), std::end(vector), [&engine, &distribution]()
		{ 
			return distribution(engine);
		}
	);

//  --------------------------------------------------------------------

	test(vector);
}