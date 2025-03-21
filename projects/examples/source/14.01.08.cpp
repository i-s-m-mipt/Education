#include <algorithm>
#include <cassert>
#include <cmath>
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
		sum = std::reduce(std::begin(view), std::end(view));
	}
};

///////////////////////////////////////////////////////////////////////////////////

template < std::ranges::view V, typename T > auto reduce(V view, T sum)
{
    auto begin = std::begin(view), end = std::end(view);

//  -------------------------------------------------------------------------------

	if (auto size = std::distance(begin, end); size > 0)
	{
		auto concurrency = std::max(std::thread::hardware_concurrency(), 2u);

	//  ---------------------------------------------------------------------------

		std::vector < T > sums(concurrency, T(0));

	//  ---------------------------------------------------------------------------

		auto step = size / concurrency;

		auto begin_block = begin, end_block = std::next(begin_block, step);

	//  ---------------------------------------------------------------------------

		{
			std::vector < std::jthread > threads(concurrency - 1);

		//  -----------------------------------------------------------------------

			for (auto i = 0uz; i < std::size(threads); ++i)
			{
				auto range = std::ranges::subrange(begin_block, end_block);

			//  ------------------------------------------------------------

				threads[i] = std::jthread
				(
					Task < decltype(range), T > (), range, std::ref(sums[i])
				);

			//  ------------------------------------------------------------

				begin_block = end_block;
				
				end_block = std::next(begin_block, step);
			}

		//  -----------------------------------------------------------------------

			auto range = std::ranges::subrange(begin_block, end);

		//  -----------------------------------------------------------------------

			Task < decltype(range), T > ()(range, std::ref(sums[concurrency - 1]));
		}

	//  ---------------------------------------------------------------------------

		sum += std::reduce(std::begin(sums), std::end(sums), T(0));
	}

//  -------------------------------------------------------------------------------
	
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