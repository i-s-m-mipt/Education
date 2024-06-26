#include <iomanip>
#include <iostream>
#include <iterator>
#include <typeinfo>
#include <vector>

#include <boost/multi_array.hpp>

//  ================================================================================================

template < auto N, typename C, typename FI > inline void fill_shape(const C & container, FI shape) noexcept
{
	if constexpr (*shape = std::size(container); N > 1)
	{
		fill_shape < N - 1 > (*(std::begin(container)), ++shape);
	}
}

//  ================================================================================================

template < auto N, typename C, typename FI > inline void fill_array(const C & container, FI array) noexcept
{
	if constexpr (N > 1)
	{
		for (const auto & element : container) fill_array < N - 1 > (element, (array++)->begin());
	}
	else
	{
		for (const auto & element : container) *(array++) = element;
	}
}

//  ================================================================================================

template < typename T, auto N, typename C > [[nodiscard]] auto make_array(const C & c)
{
	using array_t = boost::multi_array < T, N > ;

	std::vector shape(N, typename array_t::index(0));

	fill_shape < N > (c, std::begin(shape)); array_t array(shape); // detail: 3 x 4 x 5
	fill_array < N > (c, std::begin(array));

	return array;
}

//  ================================================================================================

int main()
{
	constexpr std::size_t size_1 = 3;
	constexpr std::size_t size_2 = 4;
	constexpr std::size_t size_3 = 5;

//  ================================================================================================

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

//  ================================================================================================

	const auto array = make_array < int, 3 > (vector_3D);

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