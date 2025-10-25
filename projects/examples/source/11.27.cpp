////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

auto next(std::vector < std::size_t > & steps, std::vector < std::size_t > const & sizes)
{
	auto has_next = false;

	for (auto i = std::ssize(steps) - 1; i >= 0; --i)
	{
		++steps[i];

		if (steps[i] == sizes[i])
		{
			steps[i] = 0;
		}
		else
		{
			has_next = true;

			break;
		}
	}

	return has_next;
}

////////////////////////////////////////////////////////////////////////////////////////////////

template < std::size_t ... Is > void invoke
(
	auto && f, auto && tuple, std::vector < std::size_t > const & steps,

	std::index_sequence < Is ... >
)
{
	f(*std::next(std::get < Is > (tuple).first, steps[Is])...);
}

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Is > auto cartesian(std::pair < Is, Is > ... pairs)
{
	std::vector < std::tuple < typename std::iterator_traits < Is > ::value_type ... > > tuples;

	std::vector < std::size_t > steps(sizeof...(pairs), 0);

	std::vector < std::size_t > sizes = 
	{ 
		static_cast < std::size_t > (std::distance(pairs.first, pairs.second))... 
	};

	auto lambda = [&tuples](auto ... pairs){ tuples.emplace_back(pairs...); };

	do
	{
		invoke
		(
			lambda, std::tie(pairs...), steps,

			std::make_index_sequence < sizeof...(pairs) > ()
		);
	} 
	while (next(steps, sizes));

	return tuples;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector_1 = { 1, 2, 3, 4, 5 };

	std::vector < int > vector_2 = { 1, 2, 3 };

//  -------------------------------------------------------------

	auto tuples = cartesian
	(	
		std::make_pair(std::begin(vector_1), std::end(vector_1)),

		std::make_pair(std::begin(vector_2), std::end(vector_2))
	);

//  -------------------------------------------------------------

	auto size = std::size(vector_2);

//  -------------------------------------------------------------

	for (auto i = 0uz; i < std::size(vector_1); ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			auto tuple = tuples[i * size + j];

		//  ----------------------------------------------

			assert(std::get < 0 > (tuple) == vector_1[i]);

			assert(std::get < 1 > (tuple) == vector_2[j]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////