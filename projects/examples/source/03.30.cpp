////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////

class Vector
{
public :

	Vector() : m_array(nullptr), m_size(0) 
	{
		std::cout << "Vector:: Vector (1)\n";
	}

//  --------------------------------------------------------------------------------

	Vector(std::initializer_list < int > list) : m_size(std::size(list))
	{
		std::cout << "Vector:: Vector (2)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(list, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector const & other) : m_size(other.m_size) 
	{
		std::cout << "Vector:: Vector (3)\n";

		m_array = m_size ? new int[m_size]{} : nullptr;

		std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
	}

//  --------------------------------------------------------------------------------

	Vector(Vector && other)
	: 
		m_array(std::exchange(other.m_array, nullptr)), 
		
		m_size (std::exchange(other.m_size,  0      ))
	{
		std::cout << "Vector:: Vector (4)\n";
	}

//  --------------------------------------------------------------------------------

   ~Vector()
	{
		std::cout << "Vector::~Vector\n";

		delete[] m_array;
	}
	
//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // error
//	{
//		std::cout << "Vector::operator= (1)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//
//			m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector const & other) // bad
//	{
//		std::cout << "Vector::operator= (2)\n";
//
//		if (this != &other)
//		{
//			auto array = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			std::ranges::copy(other.m_array, other.m_array + other.m_size, array);		
//		
//			delete[] std::exchange(m_array, array);
//
//			m_size = other.m_size;
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::cout << "Vector::operator= (3)\n";
//
//		if (this != &other)
//		{
//			delete[] m_array;
//			
//			m_array = std::exchange(other.m_array, nullptr);
//
//			m_size  = std::exchange(other.m_size,  0      );
//		}
//
//		return *this;
//	}

//  --------------------------------------------------------------------------------

	auto & operator=(Vector other)
	{
		std::cout << "Vector::operator= (4)\n";

		swap(other);

		return *this;
	}

//  --------------------------------------------------------------------------------

	void swap(Vector & other)
	{
		std::swap(m_array, other.m_array);
		
		std::swap(m_size,  other.m_size );
	}

private :

	int * m_array = nullptr;

	std::size_t m_size = 0;
};

////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Vector vector_1;

	Vector vector_2 = { 1, 2, 3, 4, 5 };

	Vector vector_3 = vector_2;

	Vector vector_4 = std::move(vector_3);

//  --------------------------------------

	vector_3 = vector_2;

	vector_4 = std::move(vector_3);
}

////////////////////////////////////////////////////////////////////////////////////