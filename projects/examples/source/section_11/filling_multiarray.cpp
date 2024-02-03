#include <iomanip>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>

#include <boost/multi_array.hpp>

template < auto N, typename C, typename FI > void fill_shape(const C & c, FI shape)
{
	*shape = std::size(c);

	if constexpr (N > 1)
	{
		fill_shape < N - 1 > (*(std::begin(c)), ++shape);
	}
}

template < auto N, typename C, typename FI > void fill_array(const C & c, FI array)
{
	if constexpr (N > 1)
	{
		for (auto iterator = std::begin(c); iterator != std::end(c); ++iterator)
		{
			fill_array < N - 1 > (*iterator, (array++)->begin());
		}
	}
	else
	{
		for (auto iterator = std::begin(c); iterator != std::end(c); ++iterator)
		{
			*(array++) = *iterator;
		}
	}
}

template < typename T, auto N, typename C > auto make_array(const C & c)
{
	using array_t = boost::multi_array < T, N > ;

	std::vector shape(N, array_t::index(0));

	fill_shape < N > (c, std::begin(shape)); array_t array(shape); // note: 3x4x5
	fill_array < N > (c, std::begin(array));

	return array;
}

int main()
{
	const std::size_t size_1 = 3;
	const std::size_t size_2 = 4;
	const std::size_t size_3 = 5;

	std::vector < std::vector < std::vector < int > > > vector_3D(size_1,
		          std::vector < std::vector < int > >            (size_2,
			                    std::vector < int >              (size_3, 0)));

	std::cout << "std::vector < std::vector < std::vector < int > > > " << std::endl << std::endl;

	auto counter = 0;

	for (std::size_t i = 0; i < size_1; ++i)
	{
		for (std::size_t j = 0; j < size_2; ++j)
		{
			for (std::size_t k = 0; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::right << (vector_3D[i][j][k] = ++counter) << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	auto array = make_array < int, 3 > (vector_3D);

	std::cout << typeid(array).name() << std::endl << std::endl;

	for (std::size_t i = 0; i < size_1; ++i)
	{
		for (std::size_t j = 0; j < size_2; ++j)
		{
			for (std::size_t k = 0; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::right << array[i][j][k] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	return 0;
}