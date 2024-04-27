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

// =================================================================================================

template < typename F, typename ... Ts > 

[[nodiscard]] inline constexpr decltype(auto) async_invoke(F && f, Ts && ... args)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (args)...);
}

// =================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
	const auto first = std::ranges::cbegin(view), last = std::ranges::cend(view);

	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25; // note: only for demonstration

	if (length <= max_size)
	{
		return std::reduce(first, last, sum);
	}
	else
	{
		const auto middle = std::next(first, length / 2);

        std::ranges::subrange left(first, middle);

		auto result_1 = std::async(reduce < decltype(left), T > , left, sum);

		auto result_2 = reduce(std::ranges::subrange(middle, last), T());

		return result_1.get() + result_2; // note: synchronization with main thread
	}
}

// =================================================================================================

int main()
{
    auto future = std::async(std::launch::deferred, []() constexpr noexcept { return 42; });

    assert(future.get() == 42); // note: synchronization with main thread, deferred function called

    try
    {
        std::async(std::launch::async, [](){ throw std::runtime_error("error"); }).get();
    }
    catch(const std::exception & exception) // good: catch exception from async function
    {
        std::cerr << exception.what() << '\n';
    }

	constexpr std::size_t size = 100;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	assert(reduce(std::views::all(vector), 0) == 5050);

	return 0;
}