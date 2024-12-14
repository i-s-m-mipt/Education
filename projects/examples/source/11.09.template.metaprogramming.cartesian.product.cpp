#include <concepts>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

//  ================================================================================================

auto next(std::vector < std::size_t > & steps, const std::vector < std::size_t > & sizes)
{
	auto has_next = false;

	for (int i = static_cast < int > (std::size(steps)) - 1; i >= 0; --i)
	{
		if (steps[i]++; steps[i] == sizes[i])
		{
			steps[i] = 0;
		}
		else
		{
			has_next = true; break;
		}
	}

	return has_next;
}

//  ================================================================================================

template < typename F, typename T, std::size_t ... Is > void apply
(
	F && f, T && tuple, const std::vector < std::size_t > & steps,

	std::integer_sequence < std::size_t, Is ... >
)
{
	f(*(std::next(std::get < Is > (tuple).first, steps[Is]))...);
}

//  ================================================================================================

template < std::forward_iterator ... Is > auto generate(std::pair < Is, Is > ... args)
{
	std::vector < std::tuple < typename std::iterator_traits < Is > ::value_type ... > > result;

	std::vector < std::size_t > steps(sizeof...(args), 0);

	std::vector < std::size_t > sizes
	{ 
		static_cast < std::size_t > (std::distance(args.first , args.second))... 
	};

	do
	{
		apply
		(
			[&result](auto && ... args)
			{ 
				result.emplace_back(args...); 
			}, 
			std::tie(args...), steps, std::make_integer_sequence < std::size_t, sizeof...(args) > ()
		);
	} 
	while (next(steps, sizes));

	return result;
}

//  ================================================================================================

int main()
{
    std::vector < int > vector_1 { 1, 2, 3, 4, 5 };
	std::vector < int > vector_2 { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------------

	auto result = generate
	(	
		std::make_pair(std::begin(vector_1), std::end(vector_1)),
		std::make_pair(std::begin(vector_2), std::end(vector_2))
	);

//  ---------------------------------------------------------------

	std::cout << '\n';

	std::cout << std::setprecision(1) << std::fixed;

	for (auto [x, y] : result)
	{
		std::cout << "pair = { " << x << ", " << y << " }\n";
	}

	std::cout << '\n';
}