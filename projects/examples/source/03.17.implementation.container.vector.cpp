#include <algorithm>
#include <iostream>
#include <utility>

class Container
{
public:

	using data_t = int;

public:

	Container() : m_data(nullptr), m_size(0) 
	{
		std::cout << "constructor (main)" << std::endl;
	}

	Container(std::size_t size) : m_size(size)
	{
		std::cout << "constructor (user)" << std::endl;

		m_data = new data_t[m_size]{};
	}

	Container(const Container & other) : m_size(other.m_size) 
	{
		std::cout << "constructor (copy)" << std::endl;

		m_data = new data_t[m_size];

		std::ranges::copy(other.m_data, other.m_data + m_size, m_data); // note: deep copy range
	}

	/*
	Container(Container && other) : m_data(other.m_data), m_size(other.m_size) // note: shallow copy
	{
		std::cout << "constructor (move)" << std::endl;

		other.m_data = nullptr; // note: valid state for other object
		other.m_size = 0;       // note: valid state for other object
	}
	*/

	Container(Container && other) : Container()
	{
		std::cout << "constructor (move)" << std::endl;

		swap(other);
	}

	/*
	Container & operator=(const Container & other) // bad: ineffective and duplication
	{
		std::cout << "assignment= (copy)" << std::endl;

		if (this != &other) // note: copy self-assignment check
		{
			auto new_size = other.m_size;

			auto new_data = (new_size ? new data_t[new_size]{} : nullptr);

			std::ranges::copy(other.m_data, other.m_data + new_size, new_data); // note: deep copy range

			delete[] m_data; // good: delete after creating new data

			m_data = new_data;
			m_size = new_size;
		}

		return *this;
	}
	*/

	/*
	Container & operator=(Container && other) // bad: ineffective and duplication
	{
		std::cout << "assignment= (move)" << std::endl;

		if (this != &other) // note: move self-assignment check
		{
			if (m_data) delete[] m_data;
			
			m_data = other.m_data; // note: shallow copy
			m_size = other.m_size; // note: shallow copy

			other.m_data = nullptr; // note: valid state for other object
			other.m_size = 0;       // note: valid state for other object
		}

		return *this;
	}
	*/

	Container & operator=(Container other) // good: copy and swap idiom
	{
		std::cout << "assignment= (swap)" << std::endl;

		swap(other);

		return *this;
	}

	~Container()
	{
		std::cout << "destructor" << std::endl;

		if (m_data) delete[] m_data;
	}

public:

	void swap(Container & other) // good: useful member function
	{
		using std::swap; // good: enable argument-dependent lookup

		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
	}

private:

	data_t * m_data; std::size_t m_size;

}; // class Container

inline void swap(Container & x, Container & y) // good: useful free function
{
	x.swap(y);

//	auto t = static_cast < Container && > (x); // note: effective swap
//	     x = static_cast < Container && > (y);
//	     y = static_cast < Container && > (t);
}

int main()
{
	const std::size_t size = 5;

	Container container_1                          ; // note: constructor (main)
	Container container_2(                   size ); // note: constructor (user)

	Container container_3(            container_2 ); // note: constructor (copy)
	Container container_4(  std::move(container_3)); // note: constructor (move)

	          container_1 =           container_3  ; // note: assignment= (copy)
	          container_1 = std::move(container_3) ; // note: assignment= (move)

	return 0;
}