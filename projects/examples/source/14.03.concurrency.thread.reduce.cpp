#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <vector>

//  ================================================================================================

template < std::ranges::view V, typename T > class Task
{
public:

	void operator()(V view, T & sum) const
	{
		sum = std::reduce(std::begin(view), std::end(view));
	}
};

//  ================================================================================================

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
    auto begin = std::begin(view), end = std::end(view);

	if (auto size = 1uz * std::distance(begin, end); size > 0) 
	{
		auto concurrency = 1uz * std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < T > results(concurrency, T(0));

		auto step = size / concurrency;

		auto block_begin = begin, block_end = std::next(block_begin, step);

		{
			std::vector < std::jthread > threads(concurrency - 1);

			for (auto i = 0uz; i < std::size(threads); ++i)
			{
				auto range = std::ranges::subrange(block_begin, block_end);

				threads[i] = std::jthread
				(
					Task < decltype(range), T > (), range, std::ref(results[i])
				);

				block_begin = block_end; block_end = std::next(block_begin, step);
			}

			auto range = std::ranges::subrange(block_begin, end);

			Task < decltype(range), T > ()(range, std::ref(results[concurrency - 1]));
		}

		sum += std::reduce(std::begin(results), std::end(results), T(0));
	}
	
	return sum;
}

//  ================================================================================================

int main()
{
	std::vector < int > vector(1'000, 0);

	std::ranges::iota(vector, 1);

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}