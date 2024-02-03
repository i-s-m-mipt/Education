#include <iostream>

class Base // note: polymorphic base class
{
public:

	virtual ~Base() {}

	virtual Base * get() { return this; }

	void print() const { std::cout << "Base" << std::endl; }

}; // class Base

class Derived : public Base
{
public:

	Derived * get() override { return this; }

	void print() const { std::cout << "Derived" << std::endl; }

}; // class Derived : public Base

int main()
{
	auto d = new Derived; Base * b = d;

	d->get()->print(); // note: outputs Derived
	b->get()->print(); // note: outputs Base

	delete b;

	return 0;
}