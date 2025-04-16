////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cmath>
#include <concepts>
#include <functional>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V > class Task
{
public :

	auto operator()(V view) const
	{
		return *std::ranges::fold_left_first(view, std::plus());
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0) 
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < std::pair < std::future < T > , std::jthread > > futures(concurrency - 1);

		auto step = size / concurrency;

		auto begin_block = begin, end_block = std::next(begin_block, step);

		for (auto & [future, thread] : futures)
		{
			auto range = std::ranges::subrange(begin_block, end_block);

			std::packaged_task task { Task < decltype(range) > () };

			future = task.get_future();
			
			thread = std::jthread(std::move(task), range);

			begin_block = end_block;
			
			end_block = std::next(begin_block, step);
		}

		auto range = std::ranges::subrange(begin_block, end);

		sum += Task < decltype(range) > ()(range);

		for (auto & future : futures) 
		{
			sum += future.first.get();
		}
	}

	return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1'000, 0);

//  --------------------------------------------------------------

	std::ranges::iota(vector, 1);

//  --------------------------------------------------------------

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}

////////////////////////////////////////////////////////////////////////////////////////////////