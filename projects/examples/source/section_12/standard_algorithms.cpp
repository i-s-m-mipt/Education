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
	constexpr std::size_t size = 10;

	std::vector < int > v1(size), v2(size), v3; // note: initially empty sequences, inserters required

	std::iota(std::begin(v1), std::end(v1), 0); // note: v1 contains 0 1 2 3 4 5 6 7 8 9

	std::mt19937_64 engine(std::random_device{}());

	std::shuffle(std::begin(v1), std::end(v1), engine); // note: random with no duplicates

	if (const auto element = std::find(std::cbegin(v1), std::cend(v1), 0); element != std::cend(v1))
	{
		assert(*element == 0); // good: iterator dereferencing only after verification
	}

	const auto [min, max] = std::minmax_element(std::cbegin(v1), std::cend(v1)); // note: structured binding

	std::uniform_int_distribution distribution(*min, *max);

	const auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate(std::begin(v2), std::end(v2), generator); // note: random with duplicates

	constexpr auto is_even = [](auto x){ return (x % 2 == 0); };

//	v2.erase(std::remove_if(std::begin(v2), std::end(v2), is_even), std::end(v2)); // bad: too long

	std::erase_if(v2, is_even); // note: one algorithm instead of erase member + remove_if

	v3.reserve(std::size(v2)); // good: reserve enough memory before push_back through back_inserter

	std::sample(std::cbegin(v1), std::cend(v1), std::back_inserter(v3), std::size(v2), engine);

	std::transform(std::cbegin(v2), std::cend(v2), std::cbegin(v3), std::begin(v3), std::plus());

	std::for_each(std::cbegin(v3), std::cend(v3), [](auto x){ std::cout << x <<  ' '; });

	std::cout << std::endl;

	return 0;
}