#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <utility>
#include <vector>

//  ================================================================================================

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

//  ================================================================================================

int main()
{
	auto size = 5uz;

	std::vector < int > vector_1(size, 0);
	std::vector < int > vector_2(size, 0);
	std::vector < int > vector_3;

//  ================================================================================================

	std::ranges::iota(vector_1, 0);

	std::random_device device;

	std::mt19937_64 engine(device());

	std::shuffle(std::begin(vector_1), std::end(vector_1), engine);

//  ================================================================================================

	auto element = std::find(std::cbegin(vector_1), std::cend(vector_1), 0);

	if (element != std::cend(vector_1))
	{
		assert(*element == 0);
	}

	auto [min, max] = std::minmax_element(std::cbegin(vector_1), std::cend(vector_1));

	std::uniform_int_distribution distribution(*min, *max);

	auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate(std::begin(vector_2), std::end(vector_2), generator);

//  ================================================================================================

	auto is_even = [](auto x){ return x % 2 == 0; };
	auto is_five = [](auto x){ return x     == 5; };

	auto is_even_or_five = bind(is_even, is_five, std::logical_or <> ());

	[[maybe_unused]] auto tail_begin = std::remove_if
	(
		std::begin(vector_2), std::end(vector_2), is_even_or_five
	);

//	vector_2.erase(tail_begin, std::end(vector_2)); // bad

	std::erase_if(vector_2, is_even_or_five);

//  ================================================================================================

	vector_3.resize(std::size  (vector_2));

	std::sample    (std::cbegin(vector_1), 
				    std::cend  (vector_1), 
				    std:: begin(vector_3), 
				    std::size  (vector_2), engine);

	std::transform (std::cbegin(vector_2), 
				    std::cend  (vector_2), 
				    std::cbegin(vector_3), 
				    std:: begin(vector_3), std::plus());

	std::for_each  (std::cbegin(vector_3), 
				    std::cend  (vector_3), [](auto x){ std::cout << x <<  ' '; });

	std::cout << std::endl;
}