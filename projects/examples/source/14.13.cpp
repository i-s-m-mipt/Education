////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

////////////////////////////////////////////////////////////////////////////////////////////////

// section : Threads

////////////////////////////////////////////////////////////////////////////////////////////////

// content : Parallel Range Folding Algorithm
//
// content : Promises
//
// content : Wrapper std::promise

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

template < std::ranges::view V, typename T > class Task
{
public :

	void operator()(V view, std::promise < T > && promise) const
	{
		promise.set_value(*std::ranges::fold_left_first(view, std::plus()));
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto fold(std::ranges::view auto view, T sum)
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0) 
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < std::pair < std::future < T > , std::jthread > > futures(concurrency - 1);

		auto step = size / concurrency;

		for (auto & [future, thread] : futures)
		{
			auto range = std::ranges::subrange(begin, std::next(begin, step));

			std::promise < T > promise;

			future = promise.get_future();

			thread = std::jthread
			(
				Task < decltype(range), T > (), range, std::move(promise)
			);

			std::advance(begin, step);
		}

		auto range = std::ranges::subrange(begin, end);

		sum += *std::ranges::fold_left_first(range, std::plus());

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