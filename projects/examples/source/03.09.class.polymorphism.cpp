#include <iostream>
#include <vector>

//  ================================================================================================

class Computer 
{
public:

	Computer()
	{
//		print(); // bad: базовая версия
	}

	virtual ~Computer()
	{
//		print(); // bad: базовая версия
	}

	virtual void print() const { std::cout << "Computer::print" << std::endl; }

}; // class Computer

//  ================================================================================================

class Mobile final : public Computer
{
public:

	void print() const override final { std::cout << "Mobile::print" << std::endl; }

}; // class Mobile final : public Computer

//  ================================================================================================

/*
class Tablet : public Mobile // error
{
public:

	void print() const override { std::cout << "Tablet::print" << std::endl; } // error

}; // class Tablet : public Mobile
*/

//  ================================================================================================

class Laptop : public Computer 
{
public: 

	void print() const override { std::cout << "Laptop::print" << std::endl; }

}; // class Laptop : public Computer

//  ================================================================================================

class Abstract_Base // support: интерфейсы Java
{
public:

	virtual ~Abstract_Base() {};

	virtual void print() const = 0;

}; // class Abstract_Base

void Abstract_Base::print() const { std::cout << "Abstract_Base::print" << std::endl; }

//  ================================================================================================

class Derived : public Abstract_Base
{
public:

	void print() const override
	{
		std::cout << "Derived::print" << std::endl;

		Abstract_Base::print();
	}

}; // class Derived : public Abstract_Base

//  ================================================================================================

int main()
{
	const Mobile mobile;

	const Computer * computer_ptr = &mobile;

//	const Computer   computer     =  mobile; // bad: срезка объекта

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

	delete computer_ptr;

//  ================================================================================================

	const Abstract_Base * const abstract_base_ptr = new const Derived();

	abstract_base_ptr->print(); 
	
	delete abstract_base_ptr;

//	const Abstract_Base abstract_base; // error

	return 0;
}