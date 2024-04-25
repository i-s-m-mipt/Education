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

	std::vector < int > vector_1(size), vector_2(size), vector_3; // note: initially empty

	std::iota(std::begin(vector_1), std::end(vector_1), 0); // note: vector_1 contains 0 1 2 3 4 5 6 7 8 9

	std::mt19937_64 engine(std::random_device{}());

	std::shuffle(std::begin(vector_1), std::end(vector_1), engine); // note: random with no duplicates

	if (const auto element  = std::find(std::cbegin(vector_1), 
									    std::cend  (vector_1), 0); element !=           
										std::cend  (vector_1))
	{
		assert(*element == 0); // good: iterator dereferencing only after verification
	}

	const auto [min, max] = std::minmax_element(std::cbegin(vector_1), std::cend(vector_1));

	std::uniform_int_distribution distribution(*min, *max);

	const auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate(std::begin(vector_2), std::end(vector_2), generator); // note: random with duplicates

	constexpr auto is_even = [](auto x) constexpr noexcept { return (x % 2 == 0); };

	[[maybe_unused]] auto tail_begin = std::remove_if(std::begin(vector_2), std::end(vector_2), is_even);

//	vector_2.erase(tail_begin, std::end(vector_2)); // bad: redundant member function and remove_if

	std::erase_if(vector_2, is_even); // note: 1 algorithm instead of member function and remove_if

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

	return 0;
}