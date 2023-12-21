#include <cassert>
#include <iostream>
#include <string>

class X
{
public:

	explicit X(std::size_t index) : m_index(index)
	{
		std::cout << "X::CTOR called, index: " << m_index << std::endl;
	}

	~X()
	{
		std::cout << "X::DTOR called, index: " << m_index << std::endl;
	}

private:

	std::size_t m_index;

}; // class X

union U
{
	U() : s1() {}

	~U() {} // note: what should be destroyed here?

	std::string s1;
	std::string s2;

}; // union U

int main()
{
	assert(sizeof(X) == sizeof(std::size_t));

	const std::size_t size = 5;

	auto ptr = static_cast < X * > (operator new(sizeof(X) * size)); // note: uninitialized memory

	for (std::size_t i = 0; i < size; ++i)
	{
		new (ptr + i) X(i); // note: placement new, construction without allocation
	}

	const std::size_t offset = size / 2;

	(ptr + offset)->~X();

	new (ptr + offset) X(42); // note: object reconstruction in the same memory cell

	for (std::size_t i = 0; i < size; ++i)
	{
		ptr[i].~X();
	}

	operator delete(ptr); // note: uninitialized memory

	std::cout << sizeof(U) << std::endl;

	U u; // note: prefer using std::variant

	u.s1 = "hello";

	u.s1.~basic_string(); // good: explicit member destructor call

	new (&u.s2) std::string;

	u.s2 = "world";

	u.s2.~basic_string(); // good: explicit member destructor call

	return 0;
}