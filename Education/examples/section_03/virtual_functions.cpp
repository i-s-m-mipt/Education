#include <iostream>

class A
{
public:

	A()
	{
//		print(); // bad: base version
	}

	virtual ~A()
	{
//		print(); // bad: base version
	}

public:

	virtual void print() const // note: can be redefined in derived classes
	{
		std::cout << "A" << std::endl;
	}
};

class B final : public A // note: final class in hierarchy
{
public:

	B(int number) : m_number(number) {}

public:

	void print() const override final // note: final function in hierarchy
	{
		std::cout << "B " << m_number << std::endl;
	}

	auto number() const
	{
		return m_number;
	}

private:

	int m_number = 0;
};

/*
class C final : public B // error: class B declared final
{
public:

	void print() const override // error: print declared final in class B
	{
		std::cout << "C" << std::endl;
	}
};
*/

class Base // note: static Base virtual table
{
public:

	virtual ~Base() {};

public:

	virtual void f() const {};
	virtual void g() const {};

protected:

//	virtual_table * __vptr; // note: implicit data member of base class
};

class Derived_1 : public Base // note: static Derived_1 virtual table, inherited __vptr
{
public:

	void f() const override {};
};

class Derived_2 : public Base // note: static Derived_2 virtual table, inherited __vptr
{
public:

	void g() const override {};
};

class Abstract_Base // note: interface class like in Java
{
public:

	virtual ~Abstract_Base() {};

public:

	virtual void print() const = 0; // note: must be redefined in derived classes
};

void Abstract_Base::print() const // note: definition must be provided separately
{
	std::cout << "default implementation" << std::endl;
}

class Derived : public Abstract_Base
{
public:

	void print() const override
	{
		std::cout << "derived implementation" << std::endl;

		Abstract_Base::print(); // note: possible default implementation
	}
};

int main()
{
	B b(0);

	A * a_ptr = &b; // note: works with pointers and references

//	A a = b; // bad: object slicing

	a_ptr->print();

	const auto size = 3;

	B b1(1);
	B b2(2);
	B b3(3);

	A * pointers[size]{ &b1, &b2, &b3 };

	for (auto i = 0; i < size; ++i)
	{
		pointers[i]->print();
	}

	a_ptr = new B(0);

	a_ptr->print();

	delete a_ptr; // note: important virtual destructor

	Derived d;

	Abstract_Base * ab_ptr = &d; // good: interface class

	ab_ptr->print();

//	Abstract_Base ab; // error: abstract base class

	a_ptr = new B(42);

	auto b1_ptr = dynamic_cast < B * > (a_ptr); // note: provides runtime type checking

	auto b2_ptr = static_cast < B * > (a_ptr); // note: faster, possible undefined behavior 

	std::cout << b1_ptr->number() << std::endl;
	std::cout << b2_ptr->number() << std::endl;

	delete a_ptr;

	a_ptr = new A();

	auto b3_ptr = dynamic_cast < B * > (a_ptr); // note: prefer virtual functions instead of casts

	if (!b3_ptr)
	{
		std::cout << "invalid dynamic cast" << std::endl;
	}

	delete a_ptr;

	return 0;
}