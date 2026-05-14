////////////////////////////////////////////////////////////////////////////////////

// chapter : Containers

////////////////////////////////////////////////////////////////////////////////////

// section : Nested Containers

////////////////////////////////////////////////////////////////////////////////////

// content : Multidimensional Containers

////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////

#include <boost/multi_array.hpp>

////////////////////////////////////////////////////////////////////////////////////

template < std::size_t D > void fill_v1(auto const & container, auto iterator)
{
	*iterator = std::size(container);

	if constexpr (D > 1)
	{
		fill_v1 < D - 1 > (*std::begin(container), ++iterator);
	}
}

////////////////////////////////////////////////////////////////////////////////////

template < std::size_t D > void fill_v2(auto const & container, auto iterator)
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

////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t D > auto make_array(auto const & container)
{
	std::vector < typename boost::multi_array < T, D > ::index > sizes(D);

	fill_v1 < D > (container, std::begin(sizes));

	boost::multi_array < T, D > array(sizes);

	fill_v2 < D > (container, std::begin(array));

	return array;
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  --------------------------------------------------------------------------------

	std::vector < std::vector < int > > vector(size, std::vector < int > (size, 0));

//  --------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			vector[i][j] = j + 1;
		}
	}

//  --------------------------------------------------------------------------------

	auto array = make_array < int, 2 > (vector);

//  --------------------------------------------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		for (auto j = 0uz; j < size; ++j)
		{
			assert(array[i][j] == vector[i][j]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////