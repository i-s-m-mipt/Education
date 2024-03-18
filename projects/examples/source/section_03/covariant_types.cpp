#include <iostream>

class Base 
{
public:

	virtual ~Base() {} // note: polymorphic base class

	[[nodiscard]] virtual Base * get() { return this; }

	void print() const { std::cout << "Base" << std::endl; }

}; // class Base

class Derived : public Base
{
public:

	[[nodiscard]] Derived * get() override { return this; }

	void print() const { std::cout << "Derived" << std::endl; }

}; // class Derived : public Base

int main()
{
	auto d = new Derived; Base * b = d;

	d->get()->print();
	b->get()->print();

	delete b;

	return 0;
}