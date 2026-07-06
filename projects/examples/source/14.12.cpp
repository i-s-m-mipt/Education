////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////////////////

// content : Parallel Range Folding Algorithm
//
// content : Packaged Tasks
//
// content : Wrapper std::packaged_task

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

	static auto operator()(V view)
	{
		return *std::ranges::fold_left_first(view, std::plus());
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto fold(std::ranges::view auto view, T sum)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0)
	{
		auto concurrency = std::thread::hardware_concurrency();

		std::vector < std::pair < std::future < T > , std::jthread > > futures(concurrency - 1);

		auto step = size / concurrency;

		for (auto & [future, thread] : futures)
		{
			auto range = std::ranges::subrange(begin, std::next(begin, step));

			std::packaged_task < T(decltype(range)) > task { Task < decltype(range) > () };

			future = task.get_future();

			thread = std::jthread(std::move(task), range);

			std::advance(begin, step);
		}

		auto range = std::ranges::subrange(begin, end);

		sum += Task < decltype(range) > ()(range);

		for (auto & [future, thread] : futures)
		{
			sum += future.get();
		}
	}

	return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1 << 10, 0);

//  ----------------------------------------------------

	std::ranges::iota(vector, 1);

//  ----------------------------------------------------

	assert(fold(std::views::all(vector), 0) == 524'800);
}

////////////////////////////////////////////////////////////////////////////////////////////////