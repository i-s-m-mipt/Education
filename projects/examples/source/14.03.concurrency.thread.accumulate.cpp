#include <algorithm>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename T >
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T & result)
	{
		result = std::accumulate(first, last, result);
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;

	std::vector < T > results(num_threads);
	std::vector < std::thread > threads(num_threads - 1);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		threads[i] = std::thread(
			accumulate_block < Iterator, T > (),
			block_start, block_end, std::ref(results[i])); // !

		block_start = block_end;
	}

	accumulate_block < Iterator, T > ()(block_start, last, results[num_threads - 1]);

	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));

	return std::accumulate(results.begin(), results.end(), init);
}

int main(int argc, char ** argv)
{
	std::vector < int > v(100);

	std::iota(v.begin(), v.end(), 1);

	std::cout << parallel_accumulate(v.begin(), v.end(), 0) << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}