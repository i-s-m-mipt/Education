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

template < std::ranges::view V > class Task
{
public:

	auto operator()(V view) const
	{
		return std::reduce
		(
			std::ranges::begin(view), 
			std::ranges::end  (view)
		);
	}
};

//  ================================================================================================

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
	auto begin = std::ranges::begin(view), end = std::ranges::end(view);

	if (auto size = 1uz * std::distance(begin, end); size > 0) 
	{
		auto min_size = 100uz;

		auto max_threads = (size + min_size - 1) / min_size;

		auto hardware = 1uz * std::thread::hardware_concurrency();

		auto n_threads = std::min(hardware != 0 ? hardware : 2uz, max_threads);

		auto block_size = size / n_threads;

		std::vector < std::pair < std::future < T > , std::jthread > > results(n_threads - 1);

		auto block_begin = begin, block_end = std::next(block_begin, block_size);

		for (auto & result : results)
		{
			auto range = std::ranges::subrange(block_begin, block_end);

			Task < decltype(range) > task;

			std::packaged_task packaged_task(task);

			result.first = packaged_task.get_future(); 
			
			result.second = std::jthread(std::move(packaged_task), range);

			block_begin = block_end; block_end = std::next(block_begin, block_size);
		}

		auto range = std::ranges::subrange(block_begin, end);

		sum += Task < decltype(range) > ()(range);

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

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}