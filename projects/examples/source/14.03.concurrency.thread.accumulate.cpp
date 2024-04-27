#include <cmath>
#include <concepts>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>

// =================================================================================================

template < std::input_iterator I, typename T > class Block
{
public:

    explicit Block(I first, I last, T & result) noexcept : m_first(first), m_last(last), m_result(result) {}

	void operator()() const
	{
		m_result = std::accumulate(m_first, m_last, m_result);
	}

private:

    I m_first, m_last; T & m_result;

}; // template < std::input_iterator I, typename T > class Block

// =================================================================================================

template < std::ranges::input_range R, typename T > [[nodiscard]] T parallel_accumulate(R && range, T sum)
{
	const std::size_t length = std::distance(std::ranges::begin(range), std::ranges::end(range));

	if (!length) return sum;

	const std::size_t min_elements_per_thread = 25; // note: only for demonstration

	const std::size_t max_threads = (length + min_elements_per_thread - 1) / min_elements_per_thread;

	const std::size_t hardware_threads = std::thread::hardware_concurrency();

	const std::size_t n_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / n_threads;

	std::vector < T > results(n_threads);

	std::vector < std::thread > threads(n_threads - 1); // note: why -1?

	auto block_begin = std::ranges::begin(range);

	for (std::size_t i = 0; i < (n_threads - 1); ++i)
	{
		auto block_end = std::next(block_begin, block_size);

		threads[i] = std::thread(Block(block_begin, block_end, results[i]));

		block_begin = block_end;
	}

	Block(block_begin, std::ranges::end(range), results[n_threads - 1])();

	for (auto & thread : threads) thread.join();

	return std::accumulate(std::begin(results), std::end(results), sum);
}

// =================================================================================================

int main()
{
	const std::size_t size = 100;

	std::vector < int > vector(size, 0);

	std::iota(std::begin(vector), std::end(vector), 1); // note: generate range 1, 2, 3, ...

	std::cout << parallel_accumulate(std::as_const(vector), 0) << std::endl;

	return 0;
}