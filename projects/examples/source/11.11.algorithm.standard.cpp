#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////

template < typename F1, typename F2, typename B > auto bind(F1 && f1, F2 && f2, B && binder)
{
	return [=] < typename T > (T && x) 
	{ 
		return binder(f1(std::forward < T > (x)), f2(std::forward < T > (x))); 
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

		std::uniform_int_distribution distribution(1, 5);

		auto generator = [&engine, &distribution](){ return distribution(engine); };

		std::generate(std::begin(vector), std::end(vector), generator);
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto iterator = std::find(std::begin(vector), std::end(vector), 0);

		assert(iterator == std::end(vector));

		auto [min, max] = std::minmax_element(std::begin(vector), std::end(vector));

		assert(*min == 1 && *max == 5);
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		std::default_random_engine engine;

		std::shuffle(std::begin(vector), std::end(vector), engine);

		auto position = std::size(vector) / 2;

		auto iterator = std::next(std::begin(vector), position);

		std::nth_element(std::begin(vector), iterator, std::end(vector));

		for (auto i = 0uz; i < std::size(vector); ++i)
		{
			if (i < position) { assert(vector[i] <= vector[position]); }

			if (i > position) { assert(vector[i] >= vector[position]); }
		}
	}

//  --------------------------------------------------------------------------------

	{
		std::vector < int > vector = { 1, 2, 3, 4, 5 };

		auto iterator = std::remove(std::begin(vector), std::end(vector), 0);

		vector.erase(iterator, std::end(vector));

		auto is_four = [](auto x){ return x == 4; };

		auto is_five = [](auto x){ return x == 5; };

		std::erase_if(vector, bind(is_four, is_five, std::logical_or <> ()));
	}
}