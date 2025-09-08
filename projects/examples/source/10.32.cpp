////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/multi_array.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////

template < std::size_t D, typename C, typename I > void fill_v1(C const & container, I iterator)
{
	*iterator = std::size(container);

	if constexpr (D > 1)
	{
		fill_v1 < D - 1 > (*std::begin(container), ++iterator);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

template < std::size_t D, typename C, typename I > void fill_v2(C const & container, I iterator)
{
	if constexpr (D > 1)
	{
		for (auto const & element : container) 
		{
			fill_v2 < D - 1 > (element, (iterator++)->begin());
		}
	}
	else
	{
		for (auto const & element : container) 
		{
			*iterator++ = element;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t D, typename C > auto make_array(C const & container)
{
	std::vector < typename boost::multi_array < T, D > ::index > sizes(D, 0);

	fill_v1 < D > (container, std::begin(sizes));
	
	boost::multi_array < T, D > array(sizes);
	
	fill_v2 < D > (container, std::begin(array));

	return array;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  ----------------------------------------------------------

	std::vector < std::vector < std::vector < int > > > vector
	(
		size, std::vector < std::vector < int > > 
		(
			size, std::vector < int > 
			(
				size, 0
			)
		)
	);

//  ----------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			for (auto k = 0uz; k < size; ++k)
			{
				vector[i][j][k] = k + 1;
			}
		}
	}

//  ----------------------------------------------------------

	auto array = make_array < int, 3 > (vector);

//  ----------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			for (auto k = 0uz; k < size; ++k)
			{
				assert(array[i][j][k] == vector[i][j][k]);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////