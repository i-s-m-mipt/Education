#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

//  ================================================================================================

template < std::ranges::view V > struct Block
{
	[[nodiscard]] auto operator()(V view) const
	{
		return std::reduce
		(
			std::ranges::cbegin(view), 
			std::ranges::cend  (view)
		);
	}
};

//  ================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] auto reduce(V view, T sum)
{
	auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	if (auto size = 1uz * std::distance(begin, end); size > 0) 
	{
		auto min_size = 100uz;

		auto max_threads = (size + min_size - 1) / min_size;

		auto hardware = 1uz * std::thread::hardware_concurrency();

		auto n_threads = std::min(hardware != 0 ? hardware : 2uz, max_threads);

		auto block_size = size / n_threads;

		std::vector < std::pair < std::future < T > , std::jthread > > results(n_threads - 1);

		auto first = begin, last = std::next(first, block_size);

		for (auto & result : results)
		{
			auto range = std::ranges::subrange(first, last);

			std::packaged_task task((Block < decltype(range) > ()));

			result.first = task.get_future(); result.second = std::jthread(std::move(task), range);

			first = last; last = std::next(first, block_size);
		}

		auto range = std::ranges::subrange(first, end);

		sum += Block < decltype(range) > ()(range);

		for (auto & result : results) 
		{
			sum += result.first.get();
		}
	}

	return sum;	
}

//  ================================================================================================

int main()
{
	std::vector < int > vector(1'000, 0);

	std::ranges::iota(vector, 1);

	assert(reduce(std::views::all(vector), 0) == 500'500);
}