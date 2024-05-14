#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

//  ================================================================================================

template < typename C, typename F, typename G > 

[[nodiscard]] constexpr auto combine(C combinator, F f, G g)
{
	return [=] < typename T > (T && x) { return combinator(f(std::forward < T > (x)), 
														   g(std::forward < T > (x))); };
}

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 5;

	std::vector < int > vector_1(size), vector_2(size), vector_3;

//  ================================================================================================

	std::iota(std::begin(vector_1), std::end(vector_1), 0);

	std::mt19937_64 engine(std::random_device{}());

	std::shuffle(std::begin(vector_1), std::end(vector_1), engine);

//  ================================================================================================

	if (const auto element  = std::find(std::cbegin(vector_1), 
									    std::cend  (vector_1), 0); element !=           
										std::cend  (vector_1))
	{
		assert(*element == 0);
	}

	const auto [min, max] = std::minmax_element(std::cbegin(vector_1), std::cend(vector_1));

	std::uniform_int_distribution distribution(*min, *max);

	const auto generator = [&engine, &distribution](){ return distribution(engine); };

	std::generate(std::begin(vector_2), std::end(vector_2), generator);

//  ================================================================================================

	constexpr auto is_even = [](auto x) constexpr noexcept { return (x % 2 == 0); };
	constexpr auto is_five = [](auto x) constexpr noexcept { return (x     == 5); };

	constexpr auto is_even_or_five = combine(std::logical_or <> (), is_even, is_five);

	[[maybe_unused]] auto tail_begin = std::remove_if(std::begin(vector_2), 
													  std::end  (vector_2), is_even_or_five);

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

	return 0;
}