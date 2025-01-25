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
		return std::reduce(std::begin(view), std::end(view));
	}
};

//  ================================================================================================

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = 1uz * std::distance(begin, end); size > 0) 
	{
		auto concurrency = 1uz * std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < std::pair < std::future < T > , std::jthread > > results(concurrency - 1);

		auto step = size / concurrency;

		auto block_begin = begin, block_end = std::next(block_begin, step);

		for (auto & result : results)
		{
			auto range = std::ranges::subrange(block_begin, block_end);

			Task < decltype(range) > task;

			std::packaged_task packaged_task(task);

			result.first = packaged_task.get_future(); 
			
			result.second = std::jthread(std::move(packaged_task), range);

			block_begin = block_end; block_end = std::next(block_begin, step);
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