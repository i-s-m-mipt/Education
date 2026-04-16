///////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

///////////////////////////////////////////////////////////////////////////////////

// section : Threads

///////////////////////////////////////////////////////////////////////////////////

// content : Parallel Range Folding Algorithm
//
// content : Sequential Partitioning
//
// content : View std::ranges::subrange
//
// content : Algorithm std::ranges::fold_left_first
//
// content : Functor std::plus

///////////////////////////////////////////////////////////////////////////////////

// support : perf stat ./14.09

///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > class Task
{
public :

	void operator()(V view, T & sum) const
	{
		sum = *std::ranges::fold_left_first(view, std::plus());
	}
};

///////////////////////////////////////////////////////////////////////////////////

template < typename T > auto fold(std::ranges::view auto view, T sum)
{
    auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0)
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < T > sums(concurrency, T());

		auto step = size / concurrency;

		{
			std::vector < std::jthread > threads(concurrency - 1);

			for (auto i = 0uz; i < std::size(threads); ++i)
			{
				auto range = std::ranges::subrange(begin, std::next(begin, step));

				threads[i] = std::jthread
				(
					Task < decltype(range), T > (), range, std::ref(sums[i])
				);

				std::advance(begin, step);
			}

			auto range = std::ranges::subrange(begin, end);

			Task < decltype(range), T > ()(range, sums[concurrency - 1]);
		}

		sum += *std::ranges::fold_left_first(sums, std::plus());
	}

	return sum;
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1 << 10, 0);

//  ----------------------------------------------------

	std::ranges::iota(vector, 1);

//  ----------------------------------------------------

	assert(fold(std::views::all(vector), 0) == 524'800);
}

///////////////////////////////////////////////////////////////////////////////////