#include <iostream>
#include <string>
#include <vector>

class X
{
public:

	using data_t = int;

public:

	X(data_t data) : m_data(data)
	{
		std::cout << "ctor: " << m_data << std::endl;
	}

	~X()
	{
		std::cout << "dtor: " << m_data << std::endl;
	}

public:

	const auto data() const
	{
		return m_data;
	}

private:

	data_t m_data;
};

union U
{
	U() : s() {}

	~U() {} // ?

	std::string s;
	std::vector < int > v;
};

int main()
{
	std::cout << sizeof(X) << std::endl;

	const std::size_t size = 10;

	auto ptr = static_cast < X * > (operator new(sizeof(X) * size));

	for (std::size_t i = 0; i < size; ++i)
	{
		new (ptr + i) X(static_cast < X::data_t > (i));
	}

	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << ptr[i].data() << std::endl;
	}

	const std::size_t offset = size / 2;

	(ptr + offset)->~X();

	new (ptr + offset) X(42);

	for (std::size_t i = 0; i < size; ++i)
	{
		ptr[i].~X();
	}

	operator delete(ptr);

	std::cout << sizeof(std::string)         << std::endl;
	std::cout << sizeof(std::vector < int >) << std::endl;

	std::cout << sizeof(U) << std::endl;

	U u;

	u.s = "hello";

	u.s.~basic_string();

	new (&u.v) std::vector < int > ;

	u.v.push_back(42);

	u.v.~vector();

	return 0;
}