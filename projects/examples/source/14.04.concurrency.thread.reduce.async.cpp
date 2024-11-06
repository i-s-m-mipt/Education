#include <algorithm>
#include <cassert>
#include <concepts>
#include <exception>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

//  ================================================================================================

template 
< 
	typename F, typename ... Ts 
>
[[nodiscard]] decltype(auto) async_invoke(F && f, Ts && ... args)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (args)...);
}

//  ================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
	auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	if (auto size = 1uz * std::distance(begin, end), min_size = 100uz; size > min_size)
	{
		auto middle = std::next(begin, size / 2);

        std::ranges::subrange left(begin, middle);

		auto result_1 = std::async(reduce < decltype(left), T > , left, sum);

		auto result_2 = reduce(std::ranges::subrange(middle, end), T(0));

		return result_1.get() + result_2;
	}
	else
	{
		return std::reduce(begin, end, sum);
	}
}

//  ================================================================================================

int main()
{
    auto future = std::async(std::launch::deferred, [](){ return 1; });

    assert(future.get() == 1);

    try
    {
        std::async(std::launch::async, [](){ throw std::runtime_error("error"); }).get();
    }
    catch (const std::exception & exception)
    {
        std::cerr << "main : " << exception.what() << '\n';
    }

//  ================================================================================================

	std::vector < int > vector(1'000, 0);

	std::ranges::iota(vector, 1);

	assert(reduce(std::views::all(vector), 0) == 500'500);
}