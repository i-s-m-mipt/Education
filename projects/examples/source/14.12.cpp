////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
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

template < typename T > auto reduce(std::ranges::view auto view, T sum)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0) 
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < std::pair < std::future < T > , std::jthread > > futures(concurrency - 1);

		auto step = size / concurrency;

		for (auto & [future, jthread] : futures)
		{
			auto range = std::ranges::subrange(begin, std::next(begin, step));

			std::packaged_task task { Task < decltype(range) > () };

			future = task.get_future();
			
			jthread = std::jthread(std::move(task), range);

			std::advance(begin, step);
		}

		auto range = std::ranges::subrange(begin, end);

		sum += Task < decltype(range) > ()(range);

		for (auto & [future, jthread] : futures) 
		{
			sum += future.get();
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