#include <iostream>

class Empty {};

class A {}; // note: empty base class optimization

class B : public A {};
class C : public B {};

class Container
{
public:

	Container() = default; // note: default implementation

	explicit Container(int size) : m_size(size) {}

private:

	int m_size;

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

int main()
{
	std::cout << sizeof(Empty) << std::endl; // note: non-zero size

	std::cout << sizeof(A) << std::endl;
	std::cout << sizeof(B) << std::endl;
	std::cout << sizeof(C) << std::endl;

	[[maybe_unused]] auto c1 = f(); // note: guaranteed copy elision
	[[maybe_unused]] auto c2 = g(); // note: guaranteed copy elision

	return 0;
}