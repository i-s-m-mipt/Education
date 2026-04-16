///////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

///////////////////////////////////////////////////////////////////////////

// section : Threads

///////////////////////////////////////////////////////////////////////////

// content : Parallel Range Folding Algorithm
//
// content : Recursive Partitioning

///////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <functional>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <vector>

///////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto fold(V view, T sum) -> T
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end), half = size / 2; size > 16)
	{
        std::ranges::subrange range(begin, std::next(begin, half));

		auto future = std::async(fold < decltype(range), T > , range, T());

		sum += fold(std::ranges::subrange(std::end(range), end), T());

		return sum + future.get();
	}
	else
	{
		return sum + *std::ranges::fold_left_first(view, std::plus());
	}
}

///////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1 << 10, 0);

//  ----------------------------------------------------

	std::ranges::iota(vector, 1);

//  ----------------------------------------------------

	assert(fold(std::views::all(vector), 0) == 524'800);
}

///////////////////////////////////////////////////////////////////////////