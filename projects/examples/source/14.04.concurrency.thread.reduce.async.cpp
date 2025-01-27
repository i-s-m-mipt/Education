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

/////////////////////////////////////////////////////////////////////////////////////////////////

auto test(int x, int y) 
{ 
	return x + y; 
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > decltype(auto) async_invoke(F && f, Ts && ... args)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (args)...);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto reduce(V view, T sum) -> T
{
	auto begin = std::begin(view), end = std::end(view);

	if (auto size = 1uz * std::distance(begin, end), min_size = 100uz; size > min_size)
	{
		auto middle = std::next(begin, size / 2);

        std::ranges::subrange range(begin, middle);

		auto result_1 = std::async(reduce < decltype(range), T > , range, sum);

		auto result_2 = reduce(std::ranges::subrange(middle, end), T(0));

		return result_1.get() + result_2;
	}
	else
	{
		return std::reduce(begin, end, sum);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		assert(std::async(std::launch::async,    [](){ return 1; }).get() == 1);

		assert(std::async(std::launch::deferred, [](){ return 2; }).get() == 2);
	}

//  ----------------------------------------------------------------------------

	{
		assert(async_invoke(test, 1, 2).get() == 3);
	}

//  ----------------------------------------------------------------------------

	{
		std::vector < int > vector(1'000, 0);

		std::ranges::iota(vector, 1);

		assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
	}
}