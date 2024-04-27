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

template < std::ranges::view V, typename T > [[nodiscard]] T parallel_accumulate(V view, T sum)
{
	const auto first = std::ranges::cbegin(view), last = std::ranges::cend(view);

	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25; // note: only for demonstration

	if (length <= max_size)
	{
		return std::accumulate(first, last, sum);
	}
	else
	{
		const auto middle = std::next(first, length / 2);

        std::ranges::subrange left(first, middle);

		auto result_1 = std::async(parallel_accumulate < decltype(left), T > , left, sum);

		auto result_2 = parallel_accumulate(std::ranges::subrange(middle, last), T());

		return result_1.get() + result_2; // note: synchronization with main thread
	}
}

int main()
{
    std::future < int > future = std::async(std::launch::deferred, []() constexpr noexcept { return 42; });

    assert(future.get() == 42); // note: synchronization with main thread, deferred function called

    try
    {
        std::async(std::launch::async, [](){ throw std::runtime_error("error"); }).get();
    }
    catch(const std::exception & exception) // good: catch exception from async function
    {
        std::cerr << exception.what() << '\n';
    }

	const std::size_t size = 100;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1); // note: generate range 1, 2, 3, ...

	assert(parallel_accumulate(std::views::all(vector), 0) == 5050);

	return 0;
}