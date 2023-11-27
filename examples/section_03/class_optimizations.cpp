#include <iostream>

class Container
{
public:

	Container()
	{
		std::cout << "default constructor" << std::endl;
	}

	Container([[maybe_unused]] const Container & other)
	{
		std::cout << "copy constructor" << std::endl;
	}

	Container([[maybe_unused]] Container && other)
	{
		std::cout << "move constructor" << std::endl;
	}

	Container & operator=([[maybe_unused]] const Container & other)
	{
		std::cout << "copy assignment operator" << std::endl;
	}

	Container & operator=([[maybe_unused]] Container && other)
	{
		std::cout << "move assignment operator" << std::endl;
	}

	~Container()
	{
		std::cout << "destructor" << std::endl;
	}

}; // class Container

auto f()
{
	return Container(); // note: copy elision, return value optimization
}

auto g()
{
	auto c = Container(); // note: guaranteed copy elision

	return c; // note: copy elision, named return value optimization
}

class Empty {};

class A {}; // note: empty base class optimization

class B : public A {};
class C : public B {};

int main()
{
	[[maybe_unused]] auto c1 = f(); // note: guaranteed copy elision
	[[maybe_unused]] auto c2 = g(); // note: guaranteed copy elision

	std::cout << sizeof(Empty) << std::endl; // note: non-zero size

	std::cout << sizeof(A) << std::endl;
	std::cout << sizeof(B) << std::endl;
	std::cout << sizeof(C) << std::endl;

	return 0;
}