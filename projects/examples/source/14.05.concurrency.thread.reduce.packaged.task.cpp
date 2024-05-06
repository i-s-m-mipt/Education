#include <cassert>
#include <cmath>
#include <concepts>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

//  ================================================================================================

template < std::ranges::view V > class Block
{
public:

    explicit Block(V view) noexcept : m_view(view) {}

	[[nodiscard]] auto operator()() const
	{
		return std::reduce(std::ranges::cbegin(m_view), std::ranges::cend(m_view));
	}

private:

    const V m_view;

}; // template < std::ranges::view V > class Block

//  ================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
	const auto begin = std::ranges::cbegin(view), end = std::ranges::cend(view);

	std::size_t size = std::distance(begin, end);

	if (!size) return sum;

	const std::size_t min_size = 100; // note: демонстрация

	const std::size_t max_threads = (size + min_size - 1) / min_size;

	const std::size_t hardware = std::thread::hardware_concurrency();

	const std::size_t n_threads = std::min(hardware != 0 ? hardware : 2, max_threads);

	size /= n_threads;

	std::vector < std::pair < std::future < T > , std::jthread > > results(n_threads - 1);

	auto first = begin;

	for (auto & result : results)
	{
		const auto last = std::next(first, size);

		std::packaged_task task { Block(std::ranges::subrange(first, last)) };

		result.first = task.get_future(); result.second = std::jthread(std::move(task));

		first = last;
	}

	sum += Block(std::ranges::subrange(first, end))();

	for (auto & result : results) sum += result.first.get();

	return sum;
}

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 1'000;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	assert(reduce(std::views::all(vector), 0) == 500'500);

	return 0;
}