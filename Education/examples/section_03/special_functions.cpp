#include <iostream>

class Container
{
public:

	using data_t = int;
	using size_t = int;

public:

	Container() : m_data(nullptr), m_size(0) 
	{
		std::cout << "default constructor" << std::endl;
	}

	Container(size_t size) : m_size(size)
	{
		std::cout << "main constructor" << std::endl;

		m_data = new data_t[m_size]{};
	}

	Container(const Container & other) : m_size(other.m_size) 
	{
		std::cout << "copy constructor" << std::endl;

		m_data = new data_t[m_size];

		for (size_t i = 0; i < m_size; ++i) 
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
	Container & operator=(const Container & other)
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

			delete[] m_data;

			m_data = new_data;
			m_size = new_size;
		}

		return *this;
	}
	*/

	/*
	Container & operator=(Container && other)
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

	void swap(Container & other)
	{
		using std::swap;

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

	data_t * m_data;
	size_t   m_size;
};

void swap(Container & x, Container & y)
{
	x.swap(y);
}

Container f()
{
	return Container(); // note: copy elision, return value optimization
}

Container g()
{
	Container c = Container(); // note: guaranteed copy elision

	return c; // note: copy elision, named return value optimization
}

int main()
{
	Container c1;
	Container c2(10);

	[[maybe_unused]] Container c3(c2);
	[[maybe_unused]] Container c4(static_cast < Container && > (c2)); // note: xvalue

	c1 = c3;
	c1 = Container(10);

	[[maybe_unused]] auto c5 = f(); // note: guaranteed copy elision
	[[maybe_unused]] auto c6 = g(); // note: guaranteed copy elision

	return 0;
}