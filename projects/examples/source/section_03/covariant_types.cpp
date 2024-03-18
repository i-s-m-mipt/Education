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
	const auto derived = new Derived; Base * const base = derived;

	derived->get()->print(); 
	base   ->get()->print();

	delete base;

	return 0;
}