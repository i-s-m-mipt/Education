#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

int main()
{
	std::vector < int > v1, v2, v3; // note: initially empty sequences, inserters required

	std::fill_n(std::back_inserter(v1), 10, 0); // note: less effective, than constructor

	std::iota(std::begin(v1), std::end(v1), 0); // note: v1 contains 0 1 2 3 4 5 6 7 8 9

	std::mt19937 engine(std::random_device{}());

	std::shuffle(std::begin(v1), std::end(v1), engine); // note: random with no duplicates

	auto [min, max] = std::minmax_element(std::cbegin(v1), std::cend(v1)); // note: structured binding

	std::uniform_int_distribution distribution(*min, *max);

	auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate_n(std::back_inserter(v2), std::size(v1), generator); // note: random with duplicates

	auto is_even = [](auto x){ return (x % 2 == 0); };

//	v2.erase(std::remove_if(std::begin(v2), std::end(v2), is_even), std::end(v2)); // bad: too long

	std::erase_if(v2, is_even); // note: one algorithm instead of erase member + remove_if

	std::sample(std::cbegin(v1), std::cend(v1), std::back_inserter(v3), std::size(v2), engine);

	std::for_each(std::cbegin(v3), std::cend(v3), [](auto x){ std::cout << x << std::endl; });

	return 0;
}