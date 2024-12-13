#include <algorithm>
#include <iostream>
#include <utility>

//  ================================================================================================

class Vector
{
public:

	Vector() : m_data(nullptr), m_size(0) 
	{
		std::clog << "Vector::Vector (1)\n";
	}

	Vector(std::size_t size) : Vector()
	{
		std::clog << "Vector::Vector (2)\n";

		m_data = size ? new int[size]{} : nullptr;

		m_size = size;
	}

	Vector(const Vector & other) : Vector(other.m_size) 
	{
		std::clog << "Vector::Vector (3)\n";

		std::ranges::copy(other.m_data, other.m_data + other.m_size, m_data);		
	}

	Vector(Vector && other) : m_data(other.m_data), m_size(other.m_size)
	{
		std::clog << "Vector::Vector (4)\n";

		other.m_data = nullptr; 

		other.m_size = 0;
	}
	
//  ---------------------------------------------

//	auto & operator=(const Vector & other) // bad
//	{
//		std::clog << "Vector::operator= (1)\n";
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

//  ---------------------------------------------

//	auto & operator=(const Vector & other) // bad
//	{
//		std::clog << "Vector::operator= (1)\n";
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
//			m_size = size;
//		}
//
//		return *this;
//	}

//  ----------------------------------------

//	auto & operator=(Vector && other) // bad
//	{
//		std::clog << "Vector::operator= (2)\n";
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

//  ------------------------------

	auto & operator=(Vector other)
	{
		std::clog << "Vector::operator= (3)\n";

		swap(other);

		return *this;
	}

//  -----------------

   ~Vector()
	{
		std::clog << "Vector::~Vector\n";

		if (m_data) 
		{
			delete[] m_data;
		}
	}

//  -------------------------

	void swap(Vector & other)
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
	}

private:

	int * m_data = nullptr; std::size_t m_size = 0;
};

//  ================================================================================================

auto test_v1() { return Vector(); }

auto test_v2() 
{ 
	Vector vector; 
	
	return vector; 

//	return std::move(vector); // error
}

//  ================================================================================================

int main()
{
	Vector vector_1;

	Vector vector_2(5);

//  --------------------------

	Vector vector_3(vector_2);

	Vector vector_4(std::move(vector_3));

	vector_3 = vector_2;

	vector_4 = std::move(vector_3);

//  -------------------------------

	auto vector_5 = test_v1();
	auto vector_6 = test_v2();
}