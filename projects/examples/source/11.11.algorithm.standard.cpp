#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////

void test(const std::vector < int > & vector)
{
	std::cout << "test : vector = { ";

	for (auto element : vector)
	{
		std::cout << element << ' ';
	}

	std::cout << "}\n";
}

////////////////////////////////////////////////////////////////////////////////////////////

template < typename F1, typename F2, typename F3 > auto bind(F1 && f1, F2 && f2, F3 && f3)
{
	return [=] < typename T > (T && x) 
	{ 
		return f3
		(
			f1(std::forward < T > (x)), 
			
			f2(std::forward < T > (x))
		); 
	};
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::vector < int > vector(5, 0);

		std::ranges::iota(vector, 1);

		std::default_random_engine engine;

		std::shuffle(std::begin(vector), std::end(vector), engine);

		test(vector);
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector(5, 0);

		std::default_random_engine engine;

		std::uniform_int_distribution distribution(1, 5);

		auto generator = [&engine, &distribution](){ return distribution(engine); };

		std::generate(std::begin(vector), std::end(vector), generator);

		test(vector);
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::default_random_engine engine;

		std::shuffle(std::begin(vector), std::end(vector), engine);

		auto offset = std::size(vector) / 2;

		auto iterator = std::next(std::begin(vector), offset);

		std::nth_element(std::begin(vector), iterator, std::end(vector));

		for (auto i = 0uz; i < std::size(vector); ++i)
		{
			if (i < offset) { assert(vector[i] <= vector[offset]); }

			if (i > offset) { assert(vector[i] >= vector[offset]); }
		}
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto iterator = std::remove(std::begin(vector), std::end(vector), 1);

		test(vector);

		vector.erase(iterator, std::end(vector));

		assert(vector == std::vector < int > ({ 2, 3, 4, 5 }));
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto lambda_1 = [](auto x){ return x == 4; };

		auto lambda_2 = [](auto x){ return x == 5; };

		std::erase_if(vector, bind(lambda_1, lambda_2, std::logical_or <> ()));

		assert(vector == std::vector < int > ({ 1, 2, 3 }));
	}
}