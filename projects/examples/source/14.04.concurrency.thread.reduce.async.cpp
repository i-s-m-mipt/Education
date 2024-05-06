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

template < typename F, typename ... Ts > 

[[nodiscard]] inline constexpr decltype(auto) async_invoke(F && f, Ts && ... args)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (args)...);
}

//  ================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
	const auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	const std::size_t size = std::distance(begin, end);

	const std::size_t min_size = 100; // note: демонстрация
	
	if (size <= min_size)
	{
		return std::reduce(begin, end, sum);
	}
	else
	{
		const auto middle = std::next(begin, size / 2);

        std::ranges::subrange left(begin, middle);

		auto result_1 = std::async(reduce < decltype(left), T > , left, sum);

		auto result_2 = reduce(std::ranges::subrange(middle, end), T());

		return result_1.get() + result_2;
	}
}

//  ================================================================================================

int main()
{
    auto future = std::async(std::launch::deferred, []() constexpr noexcept { return 42; });

    assert(future.get() == 42);

    try
    {
        std::async(std::launch::async, [](){ throw std::runtime_error("error"); }).get();
    }
    catch(const std::exception & exception)
    {
        std::cerr << exception.what() << '\n';
    }

//  ================================================================================================

	constexpr std::size_t size = 1'000;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	assert(reduce(std::views::all(vector), 0) == 500'500);

	return 0;
}