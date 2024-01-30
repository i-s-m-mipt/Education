#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

#include <boost/multi_array.hpp>

template < auto N, typename Container, typename Forward_Iterator >
void fill_shape(const Container& container, Forward_Iterator shape)
{
	*shape = std::size(container);

	if constexpr (N > 1)
	{
		fill_shape < N - 1 >(*(std::begin(container)), ++shape);
	}
}

template < auto N, typename Container, typename Forward_Iterator >
void fill_multi_array(const Container& container, Forward_Iterator multi_array)
{
	if constexpr (N > 1)
	{
		for (const auto& element : container)
		{
			fill_multi_array < N - 1 >(element, (multi_array++)->begin());
		}
	}
	else
	{
		for (const auto& element : container)
		{
			*(multi_array++) = element;
		}
	}
}

template < typename T, auto N, typename Container >
auto make_multi_array(const Container& container)
{
	using multi_array_t = boost::multi_array < T, N >;

	std::vector < multi_array_t::index > shape(N, multi_array_t::index(0));

	fill_shape < N >(container, std::begin(shape));

	multi_array_t multi_array(shape);

	fill_multi_array < N >(container, std::begin(multi_array));

	return multi_array;
}

int main(int argc, char** argv)
{
	const auto size_1 = 3U;
	const auto size_2 = 4U;
	const auto size_3 = 5U;

	std::vector < std::vector < std::vector < int > > > v(size_1,
		std::vector < std::vector < int > >(size_2,
			std::vector < int >(size_3, 0)));

	std::cout << "std::vector < std::vector < std::vector < int > > >\n" << std::endl;

	auto counter = 0;

	for (auto i = 0U; i < size_1; ++i)
	{
		for (auto j = 0U; j < size_2; ++j)
		{
			for (auto k = 0U; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::right << (v[i][j][k] = ++counter) << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	auto multi_array = make_multi_array < int, 3U >(v);

	std::cout << "boost::multi_array\n" << std::endl;

	for (auto i = 0U; i < size_1; ++i)
	{
		for (auto j = 0U; j < size_2; ++j)
		{
			for (auto k = 0U; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::right << multi_array[i][j][k] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	system("pause");

	return EXIT_SUCCESS;
}