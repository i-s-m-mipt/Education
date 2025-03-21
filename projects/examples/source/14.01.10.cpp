#include <algorithm>
#include <cassert>
#include <concepts>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto reduce(V view, T sum) -> T
{
	auto begin = std::begin(view), end = std::end(view);

//  -------------------------------------------------------------------------

	if (auto size = std::distance(begin, end); size > 64)
	{
        std::ranges::subrange range(begin, std::next(begin, size / 2));

	//  ---------------------------------------------------------------------

		auto future = std::async(reduce < decltype(range), T > , range, sum);

	//  ---------------------------------------------------------------------

		auto sum = reduce(std::ranges::subrange(std::end(range), end), T(0));

	//  ---------------------------------------------------------------------

		return future.get() + sum;
	}
	else
	{
		return std::reduce(begin, end, sum);
	}
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1'000, 0);

//  --------------------------------------------------------------

	std::ranges::iota(vector, 1);

//  --------------------------------------------------------------

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}