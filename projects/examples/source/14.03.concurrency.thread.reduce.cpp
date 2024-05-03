#include <cassert>
#include <cmath>
#include <concepts>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

//  ================================================================================================

template < std::ranges::view V, typename T > class Block
{
public:

    explicit Block(V view, T & sum) noexcept : m_view(view), m_sum(sum) {}

	void operator()() const noexcept // note: return only by reference for std::thread
	{
		try
		{
			m_sum = std::reduce(std::ranges::cbegin(m_view), std::ranges::cend(m_view));
		}
		catch(const std::exception &) {} // good: prevents std::terminate call 
	}

private:

    const V m_view; T & m_sum;

}; // template < std::ranges::view V, typename T > class Block

//  ================================================================================================

template < std::ranges::view V, typename T > [[nodiscard]] T reduce(V view, T sum)
{
    const auto first = std::ranges::cbegin(view), last = std::ranges::cend(view);

	const std::size_t length = std::distance(first, last);

	if (!length) return sum;

	const std::size_t min_elements_per_thread = 100; // note: small limit for demonstration

	const std::size_t max_threads = (length + min_elements_per_thread - 1) / min_elements_per_thread;

	const std::size_t hardware_threads = std::thread::hardware_concurrency();

	const std::size_t n_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / n_threads;

	std::vector < T > results(n_threads, T());

	auto block_begin = first;

	{
		std::vector < std::jthread > threads(n_threads - 1); // note: why -1?

		for (std::size_t i = 0; i < std::size(threads); ++i)
		{
			const auto block_end = std::next(block_begin, block_size);

			threads[i] = std::jthread(Block(std::ranges::subrange(block_begin, block_end), results[i]));

			block_begin = block_end;
		}
	}

	Block(std::ranges::subrange(block_begin, last), results[n_threads - 1])();

	return std::reduce(std::cbegin(results), std::cend(results), sum);
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