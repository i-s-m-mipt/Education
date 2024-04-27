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

// =================================================================================================

template < std::ranges::view V, typename T > class Block
{
public:

    explicit Block(V view, T sum) noexcept : m_view(view), m_sum(sum) {}

	[[nodiscard]] T operator()() const
	{
		return std::reduce(std::ranges::cbegin(m_view), std::ranges::cend(m_view), m_sum);
	}

private:

    const V m_view; const T m_sum;

}; // template < std::ranges::view V, typename T > class Block

// =================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
	const auto first = std::ranges::cbegin(view), last = std::ranges::cend(view);

	const std::size_t length = std::distance(first, last);

	if (!length) return sum;

	const std::size_t min_elements_per_thread = 25; // note: only for demonstration

	const std::size_t max_threads = (length + min_elements_per_thread - 1) / min_elements_per_thread;

	const std::size_t hardware_threads = std::thread::hardware_concurrency();

	const std::size_t n_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / n_threads;

	std::vector < std::pair < std::future < T > , std::jthread > > results(n_threads - 1);

	auto block_begin = first;

	for (auto & result : results)
	{
		const auto block_end = std::next(block_begin, block_size);

		std::packaged_task task { Block(std::ranges::subrange(block_begin, block_end), T()) };

		result.first = task.get_future(); result.second = std::jthread(std::move(task));

		block_begin = block_end;
	}

	sum += Block(std::ranges::subrange(block_begin, last), T())();

	for (auto & result : results) sum += result.first.get();

	return sum;
}

// =================================================================================================

int main()
{
	constexpr std::size_t size = 100;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1);

	assert(reduce(std::views::all(vector), 0) == 5050);

	return 0;
}