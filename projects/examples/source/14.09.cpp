///////////////////////////////////////////////////////////////////////////////////

// support : perf stat ./14.09

///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > class Task
{
public :

	void operator()(V view, T & sum) const
	{
		sum = *std::ranges::fold_left_first(view, std::plus());
	}
};

///////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
    auto begin = std::begin(view), end = std::end(view);

	if (auto size = std::distance(begin, end); size > 0)
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

		std::vector < T > sums(concurrency, T());

		auto step = size / concurrency;

		{
			std::vector < std::jthread > jthreads(concurrency - 1);

			for (auto i = 0uz; i < std::size(jthreads); ++i)
			{
				auto range = std::ranges::subrange(begin, std::next(begin, step));

				jthreads[i] = std::jthread
				(
					Task < decltype(range), T > (), range, std::ref(sums[i])
				);

				std::advance(begin, step);
			}

			auto range = std::ranges::subrange(begin, end);

			Task < decltype(range), T > ()(range, sums[concurrency - 1]);
		}

		sum += *std::ranges::fold_left_first(sums, std::plus());
	}
	
	return sum;
}

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector(1'000, 0);

//  --------------------------------------------------------------

	std::ranges::iota(vector, 1);

//  --------------------------------------------------------------

	assert(reduce(std::ranges::views::all(vector), 0) == 500'500);
}

///////////////////////////////////////////////////////////////////////////////////