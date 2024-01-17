#include <iostream>
#include <type_traits>
#include <utility>

class Container
{
public:

	using data_t = int;

public:

	Container() : m_data(nullptr), m_size(0) 
	{
		std::cout << "default constructor" << std::endl;
	}

	Container(std::size_t size) : m_size(size)
	{
		std::cout << "main constructor" << std::endl;

		m_data = new data_t[m_size]{};
	}

	Container(const Container & other) : m_size(other.m_size) 
	{
		std::cout << "copy constructor" << std::endl;

		m_data = new data_t[m_size];

		for (std::size_t i = 0; i < m_size; ++i)
		{
			m_data[i] = other.m_data[i]; // note: deep copy
		}
	}

	/*
	Container(Container && other) : m_data(other.m_data), m_size(other.m_size) // note: shallow copy
	{
		std::cout << "move constructor" << std::endl;

		other.m_data = nullptr; // note: valid state for other object
		other.m_size = 0;       // note: valid state for other object
	}
	*/

	Container(Container && other) : Container()
	{
		std::cout << "move constructor" << std::endl;

		swap(other);
	}

	/*
	Container & operator=(const Container & other) // bad: ineffective and duplication
	{
		std::cout << "copy assignment operator" << std::endl;

		if (this != &other) // note: copy self-assignment check
		{
			auto new_size = other.m_size;

			auto new_data = (new_size ? new data_t[new_size]{} : nullptr);

			for (size_t i = 0; i < new_size; ++i)
			{
				new_data[i] = other.m_data[i]; // note: deep copy
			}

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
		std::cout << "move assignment operator" << std::endl;

		if (this != &other) // note: move self-assignment check
		{
			if (m_data)
			{
				delete[] m_data;
			}
			
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
		std::cout << "copy and swap" << std::endl;

		swap(other);

		return *this;
	}

	void swap(Container & other) // good: useful member function
	{
		using std::swap; // good: enable argument-dependent lookup

		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
	}

	~Container()
	{
		std::cout << "destructor" << std::endl;

		if (m_data)
		{
			delete[] m_data;
		}
	}

private:

	data_t * m_data; std::size_t m_size;

}; // class Container

void swap(Container & x, Container & y) // good: useful free function
{
	x.swap(y);

//	auto t = static_cast < Container && > (x); // note: effective swap
//	     x = static_cast < Container && > (y);
//	     y = static_cast < Container && > (t);
}

int main()
{
	Container c1; // note: default constructor

	Container c2(10); // note: main constructor

	Container c3(c2); // note: copy constructor

	c1 = c3; // note: copy assignment operator
	
	Container c4(static_cast < Container && > (c2)); // note: move constructor

	Container c5(std::move(c4)); // note: move constructor

	c1 = Container(10); // note: move assignment operator

	c1 = std::move(c3); // note: move assignment operator

	return 0;
}