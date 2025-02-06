#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////

class Vector
{
public:

	Vector() : m_data(nullptr), m_size(0) 
	{
		std::cout << "Vector::Vector (1)\n";
	}

	Vector(std::initializer_list < int > list) : Vector()
	{
		std::cout << "Vector::Vector (2)\n";

		auto size = std::size(list);

		m_data = size ? new int[size]{} : nullptr;

		m_size = size;

		std::ranges::copy(list, m_data);
	}

	Vector(const Vector & other) : Vector() 
	{
		std::cout << "Vector::Vector (3)\n";

		m_data = other.m_size ? new int[other.m_size]{} : nullptr;

		m_size = other.m_size;

		std::ranges::copy(other.m_data, other.m_data + other.m_size, m_data);
	}

	Vector(Vector && other) : m_data(other.m_data), m_size(other.m_size)
	{
		std::cout << "Vector::Vector (4)\n";

		other.m_data = nullptr;

		other.m_size = 0;
	}
	
//  -----------------------------------------------------------------------------

//	auto & operator=(const Vector & other) // bad
//	{
//		std::cout << "Vector::operator= (1)\n";
//
//		if (this != &other)
//		{
//			if (m_data)
//			{
//				delete[] m_data;
//			}
//
//			m_data = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			m_size = other.m_size;
//
//			std::ranges::copy(other.m_data, other.m_data + other.m_size, m_data);
//		}
//
//		return *this;
//	}

//  -----------------------------------------------------------------------------

//	auto & operator=(const Vector & other) // bad
//	{
//		std::cout << "Vector::operator= (2)\n";
//
//		if (this != &other)
//		{
//			auto data = other.m_size ? new int[other.m_size]{} : nullptr;
//
//			auto size = other.m_size;
//
//			std::ranges::copy(other.m_data, other.m_data + other.m_size, data);
//
//			if (m_data)
//			{
//				delete[] m_data;
//			}
//
//			m_data = data;
//
//			m_size = size;
//		}
//
//		return *this;
//	}

//  -----------------------------------------------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::cout << "Vector::operator= (3)\n";
//
//		if (this != &other)
//		{
//			if (m_data) 
//			{
//				delete[] m_data;
//			}
//			
//			m_data = other.m_data;

//			m_size = other.m_size;
//
//			other.m_data = nullptr;
//
//			other.m_size = 0;
//		}
//
//		return *this;
//	}

//  -----------------------------------------------------------------------------

	auto & operator=(Vector other)
	{
		std::cout << "Vector::operator= (4)\n";

		swap(other);

		return *this;
	}

//  -----------------------------------------------------------------------------

   ~Vector()
	{
		std::cout << "Vector::~Vector\n";

		if (m_data) 
		{
			delete[] m_data;
		}
	}

//  -----------------------------------------------------------------------------

	void swap(Vector & other)
	{
		std::swap(m_data, other.m_data);
		
		std::swap(m_size, other.m_size);
	}

private:

	int * m_data = nullptr; 
	
	std::size_t m_size = 0;
};

/////////////////////////////////////////////////////////////////////////////////

auto test_v1() { return Vector({ 1, 2, 3, 4, 5 }); }

auto test_v2() 
{ 
	Vector vector = { 1, 2, 3, 4, 5 };
	
	return vector;

//	return std::move(vector); // error
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Vector vector_1;

		Vector vector_2 = { 1, 2, 3, 4, 5 };

		Vector vector_3(vector_2);

		Vector vector_4(std::move(vector_3));

		vector_3 = vector_2;

		vector_4 = std::move(vector_3);
	}
	
//  -----------------------------------------

	{
		auto vector_1 = test_v1();
	
		auto vector_2 = test_v2();
	}
}