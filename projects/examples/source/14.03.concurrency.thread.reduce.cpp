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
		sum = std::reduce
		(
			std::ranges::cbegin(view), 
			std::ranges::cend  (view)
		);
	}
};

//  ================================================================================================

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
    auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	if (auto size = 1uz * std::distance(begin, end); size > 0) 
	{
		auto min_size = 100uz;

		auto max_threads = (size + min_size - 1) / min_size;

		auto hardware = 1uz * std::thread::hardware_concurrency();

		auto n_threads = std::min(hardware != 0 ? hardware : 2uz, max_threads);

		auto block_size = size / n_threads;

		std::vector < T > results(n_threads, T(0));

		auto first = begin, last = std::next(first, block_size);

		{
			std::vector < std::jthread > threads(n_threads - 1);

			for (auto i = 0uz; i < std::size(threads); ++i)
			{
				auto range = std::ranges::subrange(first, last);

				threads[i] = std::jthread
				(
					Task < decltype(range), T > (), range, std::ref(results[i])
				);

				first = last; last = std::next(first, block_size);
			}

			auto range = std::ranges::subrange(first, end);

			Task < decltype(range), T > ()(range, std::ref(results[n_threads - 1]));
		}

		sum += std::reduce(std::cbegin(results), std::cend(results), T(0));
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