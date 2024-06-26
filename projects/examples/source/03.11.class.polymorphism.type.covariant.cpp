#include <iostream>

//  ================================================================================================

class Base 
{
public:

	virtual ~Base() {}

	[[nodiscard]] virtual const Base * get() const { return this; }

	void print() const { std::cout << "Base" << std::endl; }

}; // class Base

//  ================================================================================================

class Derived : public Base
{
public:

	[[nodiscard]] const Derived * get() const override { return this; }

	void print() const { std::cout << "Derived" << std::endl; }

}; // class Derived : public Base

//  ================================================================================================

int main()
{
	const Derived * const derived = new const Derived(); 

	derived->get()->print();

	const Base * const base = derived;

	base->get()->print();

	delete base;

	return 0;
}