#include <iostream>

class Container
{
public:

	Container()
	{
		std::cout << "constructor (default)" << std::endl;
	}

	Container(const Container &)
	{
		std::cout << "constructor (copy)" << std::endl;
	}

	Container(Container &&)
	{
		std::cout << "constructor (move)" << std::endl;
	}

	Container & operator=(const Container &)
	{
		std::cout << "operator= (copy)" << std::endl; return *this;
	}

	Container & operator=(Container &&)
	{
		std::cout << "operator= (move)" << std::endl; return *this;
	}

}; // class Container

[[nodiscard]] inline Container f()
{
	return Container(); // note: copy elision, return value optimization
}

[[nodiscard]] inline Container g()
{
	const auto container = Container(); // note: guaranteed copy elision

	return container; // note: copy elision, named return value optimization
}

class E {}; // note: empty class with no data, only functions for example

class X { const char c{};                       const E e;      };
class Y { const char c{}; [[no_unique_address]] const E e;      };
class Z { const char c{}; [[no_unique_address]] const E e1, e2; };

class A {}; // note: empty base class optimization

class B : public A {};
class C : public B {};

int main()
{
	[[maybe_unused]] const auto container_1 = f(); // note: guaranteed copy elision
	[[maybe_unused]] const auto container_2 = g(); // note: guaranteed copy elision

	std::cout << "size of E: " << sizeof(E) << std::endl; // note: non-zero size

	std::cout << "size of X: " << sizeof(X) << std::endl; // note: 2 byte(s)
	std::cout << "size of Y: " << sizeof(Y) << std::endl; // note: 1 byte(s)
	std::cout << "size of Z: " << sizeof(Z) << std::endl; // note: 2 byte(s)

	std::cout << "size of A: " << sizeof(A) << std::endl; // note: 1 byte(s)
	std::cout << "size of B: " << sizeof(B) << std::endl; // note: 1 byte(s)
	std::cout << "size of C: " << sizeof(C) << std::endl; // note: 1 byte(s)

	return 0;
}