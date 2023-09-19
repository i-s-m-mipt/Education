#include <iostream>

class Person
{
public:

	Person(int age) : m_age(age)
	{
		std::cout << "person constructed\n";
	}

public:

	void print() const
	{
		std::cout << "person\n";
	}

public:

	void f([[maybe_unused]] int x) const
	{}

	void f([[maybe_unused]] char x) const
	{}

	void f([[maybe_unused]] double x) const
	{}

public:
	int m_public_data    = 0;
protected:
	int m_protected_data = 0;
private:
	int m_private_data   = 0; // good: prefer private data in hierarchies

protected:

	auto age() const
	{
		return m_age;
	}

private:

	int m_age = 0;
};

class Student : public Person
{
public:

	Student(int age, int grade) : Person(age), m_grade(grade) // good: base class constructor
	{
		std::cout << "student constructed\n";

		m_public_data    = 42;
		m_protected_data = 42;
//		m_private_data   = 42; // error: private data member
	}

public:

	void print() const
	{
		std::cout << "student\n";
	}

	auto data() const // note: extending an interface in a derived class
	{
		return m_protected_data;
	}

	using Person::age; // note: change access specifier to public

private:

	using Person::f; // note: change access specifier for all overloaded functions to private

private:

	int m_grade = 0;
};

class Employee : public Person
{
public:

	Employee(int age, int salary) : Person(age), m_salary(salary)
	{
		std::cout << "employee constructed\n";
	}

public:

	void print() const
	{
		std::cout << "employee\n";

//		print(); // error: infinite recursion

		Person::print();
	}

private:

	int m_salary = 0;
};

class Manager : public Employee
{
public:

	Manager(int age, int salary, int level) : Employee(age, salary), m_level(level)
	{
		std::cout << "manager constructed\n";
	}

public:

	void print() const
	{
		std::cout << "manager\n";
	}

private:

	int m_level = 0;
};

class B
{
public:
	int m_public_data    = 0;
protected:
	int m_protected_data = 0;
private:
	int m_private_data   = 0;
};

class D1 : public B // note: useful inheritance
{
public:
	void f()
	{
		m_public_data    = 42;
		m_protected_data = 42;
//		m_private_data   = 42; // error: private data member
	}
};

class D2 : protected B // note: useless inheritance
{
public:
	void f()
	{
		m_public_data    = 42;
		m_protected_data = 42;
//		m_private_data   = 42; // error: private data member
	}
};

class D3 : private B // note: default inheritance, prefer composition
{
	void f()
	{
		m_public_data    = 42;
		m_protected_data = 42;
//		m_private_data   = 42; // error: private data member
	}
};

class Base
{
public:
	static inline int m_common_data = 0; // note: no problems here
public:
	int m_data = 0;
};

class Left : public /*virtual*/ Base // good: virtual inheritance
{};

class Right : public /*virtual*/ Base // good: virtual inheritance
{};

class Central : public Left, public Right // note: avoid multiple inheritance
{};

int main()
{
	Manager manager(26, 100000, 5);

	manager.print();

	D1 d1;

	d1.m_public_data    = 42;
//	d1.m_protected_data = 42; // error: protected data member
//	d1.m_private_data   = 42; // error: private   data member

	[[maybe_unused]] D2 d2;

//	d2.m_public_data    = 42; // error: protected data member
//	d2.m_protected_data = 42; // error: protected data member
//	d2.m_private_data   = 42; // error: private   data member

	[[maybe_unused]] D3 d3;

//	d3.m_public_data    = 42; // error: private   data member
//	d3.m_protected_data = 42; // error: private   data member
//	d3.m_private_data   = 42; // error: private   data member

	Central central;

	central.m_common_data = 42;

//	central.m_data = 42; // error: ambiguous data member selection

	return 0;
}