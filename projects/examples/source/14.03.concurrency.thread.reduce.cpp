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

	void operator()() const noexcept
	{
		try
		{
			m_sum = std::reduce(std::ranges::cbegin(m_view), std::ranges::cend(m_view));
		}
		catch(const std::exception &) {}
	}

private:

    const V m_view; T & m_sum;

}; // template < std::ranges::view V, typename T > class Block

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

	std::vector < T > results(n_threads, T());

	auto first = begin;

	{
		std::vector < std::jthread > threads(n_threads - 1);

		for (std::size_t i = 0; i < std::size(threads); ++i)
		{
			const auto last = std::next(first, size);

			threads[i] = std::jthread(Block(std::ranges::subrange(first, last), results[i]));

			first = last;
		}
	}

	Block(std::ranges::subrange(first, end), results[n_threads - 1])();

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