#include <iostream>
#include <vector>

//  ================================================================================================

class Computer 
{
public:

	Computer()
	{
//		print(); // bad: base version
	}

	virtual ~Computer() // note: polymorphic base class
	{
//		print(); // bad: base version
	}

	virtual void print() const // note: can be redefined in derived classes
	{
		std::cout << "Computer::print" << std::endl;
	}

}; // class Computer

//  ================================================================================================

class Mobile final : public Computer // note: final class in hierarchy
{
public:

	void print() const override final // note: final function in hierarchy
	{
		std::cout << "Mobile::print" << std::endl;
	}

}; // class Mobile final : public Computer

//  ================================================================================================

/*
class Tablet : public Mobile // error: class Mobile declared final
{
public:

	void print() const override // error: print declared final in class Mobile
	{
		std::cout << "Tablet::print" << std::endl;
	}

}; // class Tablet : public Mobile
*/

//  ================================================================================================

class Laptop : public Computer // note: not final class in hierarchy
{
public:

	void print() const override // note: not final function in hierarchy
	{
		std::cout << "Laptop::print" << std::endl;
	}

}; // class Laptop : public Computer

//  ================================================================================================

class Abstract_Base // note: interface class like in Java
{
public:

	virtual ~Abstract_Base() {}; // note: polymorphic base class

	virtual void print() const = 0; // note: must be redefined in derived classes

}; // class Abstract_Base

void Abstract_Base::print() const // note: definition must be provided separately
{
	std::cout << "Abstract_Base::print" << std::endl;
}

//  ================================================================================================

class Derived : public Abstract_Base
{
public:

	void print() const override
	{
		std::cout << "Derived::print" << std::endl;

		Abstract_Base::print(); // note: possible default implementation, see pattern Decorator
	}

}; // class Derived : public Abstract_Base

//  ================================================================================================

int main()
{
	const Mobile mobile;

	const Computer * computer_ptr = &mobile; // note: works with pointers and references

//	const Computer   computer     =  mobile; // bad: object slicing

	computer_ptr->print();

//  ================================================================================================

	const Mobile mobile_1;
	const Mobile mobile_2;
	const Laptop laptop_1;
	const Laptop laptop_2;

	std::vector < const Computer * > computers { &mobile_1, &mobile_2, &laptop_1, &laptop_2 };

	for (const auto computer : computers) computer->print();

//  ================================================================================================

	computer_ptr = new const Mobile();

	computer_ptr->print();

	delete computer_ptr; // note: important virtual destructor

//  ================================================================================================

	const Abstract_Base * const abstract_base_ptr = new const Derived(); // good: interface class

	abstract_base_ptr->print(); 
	
	delete abstract_base_ptr; // good: no memory leak

//	const Abstract_Base abstract_base; // error: abstract base class

	return 0;
}