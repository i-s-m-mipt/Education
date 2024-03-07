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

	auto [min, max] = std::minmax_element(std::cbegin(v1), std::cend(v1)); // note: binding

	std::uniform_int_distribution distribution(*min, *max);

	auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate_n(std::back_inserter(v2), std::size(v1), generator); // note: duplicates

	std::erase_if(v2, [](auto x){ return (x % 2 == 0); }); // note: instead of remove_if

	std::for_each(std::begin(v2), std::end(v2), [](auto x){ assert(x % 2 != 0); });

	std::sample(std::begin(v1), std::end(v1), std::back_inserter(v3), std::size(v2), engine);

	std::copy(std::begin(v3), std::end(v3), std::ostream_iterator < int > (std::cout, " "));

	return 0;
}