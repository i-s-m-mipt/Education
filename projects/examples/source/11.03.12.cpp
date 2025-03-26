#include <cassert>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

auto next(std::vector < std::size_t > & steps, const std::vector < std::size_t > & sizes)
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

template < typename F, typename T, std::size_t ... Is > void apply
(
	F && f, T && tuple, const std::vector < std::size_t > & steps,
	
	std::integer_sequence < std::size_t, Is ... >
)
{
	f(*std::next(std::get < Is > (tuple).first, steps[Is])...);
}

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Is > auto generate(std::pair < Is, Is > ... pairs)
{
	std::vector < std::tuple < typename std::iterator_traits < Is > ::value_type ... > > tuples;

	std::vector < std::size_t > steps(sizeof...(pairs), 0);

	std::vector < std::size_t > sizes = 
	{ 
		static_cast < std::size_t > (std::distance(pairs.first , pairs.second))... 
	};

	auto lambda = [&tuples](auto ... pairs){ tuples.emplace_back(pairs...); };

	do
	{
		apply
		(
			lambda, std::tie(pairs...), steps, 
			
			std::make_integer_sequence < std::size_t, sizeof...(pairs) > ()
		);
	} 
	while (next(steps, sizes));

	return tuples;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------

	auto tuples = generate
	(	
		std::make_pair(std::begin(vector), std::end(vector)),
		
		std::make_pair(std::begin(vector), std::end(vector))
	);

//  ---------------------------------------------------------

	auto size = std::size(vector);

//  ---------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			auto tuple = tuples[i * size + j];

		//  --------------------------------------------

			assert(std::get < 0 > (tuple) == vector[i]);
			
			assert(std::get < 1 > (tuple) == vector[j]);
		}
	}
}