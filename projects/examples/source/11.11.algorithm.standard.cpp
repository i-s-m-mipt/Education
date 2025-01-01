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
		return binder
		(
			f1(std::forward < T > (x)), 
			f2(std::forward < T > (x))
		); 
	};
}

////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

	std::vector < int > vector_1(size, 0);
	std::vector < int > vector_2(size, 0);
	std::vector < int > vector_3;

//  --------------------------------------------------------------------------------

	std::ranges::iota(vector_1, 1);

	std::default_random_engine engine;

	std::shuffle(std::begin(vector_1), std::end(vector_1), engine);

//  --------------------------------------------------------------------------------

	auto iterator = std::find(std::begin(vector_1), std::end(vector_1), 0);

	if (iterator != std::end(vector_1))
	{
		assert(*iterator == 0);
	}

	auto [min, max] = std::minmax_element(std::begin(vector_1), std::end(vector_1));

	std::uniform_int_distribution distribution(*min, *max);

	auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate(std::begin(vector_2), std::end(vector_2), generator);

//  --------------------------------------------------------------------------------

	auto is_four = [](auto x){ return x == 4; };
	auto is_five = [](auto x){ return x == 5; };

	auto is_four_or_five = bind(is_four, is_five, std::logical_or <> ());

	[[maybe_unused]] auto tail_begin = std::remove_if
	(
		std::begin(vector_2), std::end(vector_2), is_four_or_five
	);

//	vector_2.erase(tail_begin, std::end(vector_2)); // bad

	std::erase_if(vector_2, is_four_or_five);

//  --------------------------------------------------------------------------------

	vector_3.resize(std::size (vector_2));

	std::sample
	(
		std::begin(vector_1), 
		std::end  (vector_1), 
		std::begin(vector_3), 
		std::size (vector_2), engine
	);

	std::transform 
	(
		std::begin(vector_2), 
		std::end  (vector_2), 
		std::begin(vector_3), 
		std::begin(vector_3), std::plus()
	);

	assert(vector_3 == std::vector < int > ({ 7, 4, 7, 4, 3 }));
}