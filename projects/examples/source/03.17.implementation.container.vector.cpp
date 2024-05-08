#include <algorithm>
#include <iostream>
#include <utility>

//  ================================================================================================

class Container
{
public:

	Container() : m_data(nullptr), m_size(0) 
	{
		std::cout << "Container::Container (main)" << std::endl;
	}

	Container(std::size_t size) : m_size(size)
	{
		std::cout << "Container::Container (user)" << std::endl;

		m_data = new int[m_size]{};
	}

	Container(const Container & other) : m_size(other.m_size) 
	{
		std::cout << "Container::Container (copy)" << std::endl;

		m_data = new int[m_size]{};

		std::ranges::copy(other.m_data, other.m_data + m_size, m_data);
	}

	/*
	Container(Container && other) : m_data(other.m_data), m_size(other.m_size)
	{
		std::cout << "Container::Container (move)" << std::endl;

		other.m_data = nullptr; other.m_size = 0;       
	}
	*/

	Container(Container && other) : Container()
	{
		std::cout << "Container::Container (move)" << std::endl;

		swap(other);
	}

	/*
	Container & operator=(const Container & other) // bad: дублирование кода
	{
		std::cout << "Container::operator= (copy)" << std::endl;

		if (this != &other)
		{
			auto new_size = other.m_size;

			auto new_data = (new_size ? new int[new_size]{} : nullptr);

			std::ranges::copy(other.m_data, other.m_data + new_size, new_data);

			delete[] m_data;

			m_data = new_data;
			m_size = new_size;
		}

		return *this;
	}
	*/

	/*
	Container & operator=(Container && other) // bad: дублирование кода
	{
		std::cout << "Container::operator= (move)" << std::endl;

		if (this != &other)
		{
			if (m_data) delete[] m_data;
			
			m_data = other.m_data;
			m_size = other.m_size;

			other.m_data = nullptr; other.m_size = 0;
		}

		return *this;
	}
	*/

	Container & operator=(Container other)
	{
		std::cout << "Container::operator= (swap)" << std::endl;

		swap(other);

		return *this;
	}

   ~Container()
	{
		std::cout << "Container::~Container" << std::endl;

		if (m_data) delete[] m_data;
	}

public:

	void swap(Container & other)
	{
		using std::swap; 

		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
	}

private:

	int * m_data; std::size_t m_size;

}; // class Container

//  ================================================================================================

inline void swap(Container & x, Container & y) { x.swap(y); }

//  ================================================================================================

int main()
{
	const std::size_t size = 5;

	Container container_1;

	Container container_2(size);

	Container container_3(container_2);

	Container container_4(std::move(container_3));

	container_1 = container_2;

	container_3 = std::move(container_4);

	swap(container_1, container_3);

	return 0;
}