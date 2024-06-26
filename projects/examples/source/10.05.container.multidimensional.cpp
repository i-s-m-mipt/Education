#include <array>
#include <iomanip>
#include <iostream>
#include <vector>

#include <boost/multi_array.hpp>

//  ================================================================================================

template < typename T, auto N > class Array_2D 
{
public:

	class Row 
	{
	public:

		constexpr explicit Row(T * array) noexcept : m_array(array) {}

		[[nodiscard]] constexpr T & operator[](std::size_t index) noexcept
		{
			return m_array[index];
		}

	private:

		T * const m_array;

	}; // class Row 

	[[nodiscard]] constexpr Row operator[](std::size_t index) noexcept 
	{
		return Row(m_array[index]);
	}

private:

	T m_array[N][N]{};

}; // template < auto N > class Array_2D

//  ================================================================================================

int main()
{
	constexpr std::size_t size = 5;

//  ================================================================================================

	[[maybe_unused]] int array_2D_v1[size][size]{};

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v1[i][j] = 42;
		}
	}

//  ================================================================================================

	Array_2D < int, size > array_2D_v2;

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v2[i][j] = 42; // support: operator()
		}
	}

//  ================================================================================================

	const auto array_2D_v3 = new int*[size]{};

	for (std::size_t i = 0; i < size; ++i)
	{
		array_2D_v3[i] = new int[size]{};
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v3[i][j] = 42;
		}
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		delete[] array_2D_v3[i];
	}

	delete[] array_2D_v3;

//  ================================================================================================

	const auto array_2D_v4 = new int[size * size]{};

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v4[i * size + j] = 42;
		}
	}

	delete[] array_2D_v4;

//  ================================================================================================

	std::array < std::array < int, size > , size > array_2D_v5;

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v5[i][j] = 42;
		}
	}

//  ================================================================================================

	std::vector array_2D_v6(size, std::vector < int > (size));

	for (std::size_t i = 0; i < size; ++i)
	{
		for (std::size_t j = 0; j < size; ++j)
		{
			array_2D_v6[i][j] = 42;
		}
	}

//  ================================================================================================

	constexpr std::size_t size_1 = 3;
	constexpr std::size_t size_2 = 4;
	constexpr std::size_t size_3 = 5;

	boost::multi_array < int, 3 > array_2D_v7(boost::extents[size_1][size_2][size_3]);

	auto index = 0;

	for (std::size_t i = 0; i < size_1; ++i)
	{
		for (std::size_t j = 0; j < size_2; ++j)
		{
			for (std::size_t k = 0; k < size_3; ++k)
			{
				std::cout << std::setw(2) << std::right << (array_2D_v7[i][j][k] = ++index) << ' ';
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

//  ================================================================================================

	using range_t = boost::multi_array_types::index_range;

	auto view = array_2D_v7[boost::indices[range_t(0, 2)][1][range_t(0, 5, 2)]];

	constexpr std::size_t view_size_1 = 2;
	constexpr std::size_t view_size_2 = 3;

	for (std::size_t i = 0; i < view_size_1; ++i)
	{
		for (std::size_t k = 0; k < view_size_2; ++k)
		{
			std::cout << std::setw(2) << std::right << view[i][k] << ' ';
		}

		std::cout << std::endl;
	}

	return 0;
}