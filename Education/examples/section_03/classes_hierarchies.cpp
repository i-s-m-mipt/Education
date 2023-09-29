#include <iostream>

class Person
{
public:

	Person(const std::string & name) : m_name(name)
	{
		std::cout << "person " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "person" << std::endl;
	}

public:

	void f([[maybe_unused]] int    x) const {}
	void f([[maybe_unused]] char   x) const {}
	void f([[maybe_unused]] double x) const {}

protected:

	const auto & name() const // good: return big object by constant reference
	{
		return m_name;
	}

private:

	std::string m_name;
};

class Student : public Person
{
public:

	Student(const std::string & name, int grade) : Person(name), m_grade(grade) // good: base class constructor
	{
		std::cout << "student " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "student" << std::endl;
	}

	using Person::name; // note: change access specifier to public

private:

	using Person::f; // note: change access specifier for all overloaded functions to private

private:

	int m_grade = 0;
};

class Employee : public Person
{
public:

	Employee(const std::string & name, int salary) : Person(name), m_salary(salary)
	{
		std::cout << "employee " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "employee" << std::endl;

//		print(); // error: infinite recursion

		Person::print();
	}

private:

	int m_salary = 0;
};

class Manager : public Employee
{
public:

	Manager(const std::string & name, int salary, int level) : Employee(name, salary), m_level(level)
	{
		std::cout << "manager " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "manager" << std::endl;
	}

private:

	int m_level = 0;
};

class B
{
public:
	int m_data_1{}; // note: avoid public data mostly
protected:
	int m_data_2{}; // note: use protected data by situation
private:
	int m_data_3{}; // good: prefer private data in hierarchies
};

class D1 : public B // note: useful inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}
};

class D2 : protected B // note: useless inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}
};

class D3 : /*private*/ B // note: default inheritance, prefer composition
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}
};

int main()
{
	Manager manager("Jenssen", 100000, 5);

	manager.print();

	D1 d1;

	d1.m_data_1 = 42;
//	d1.m_data_2 = 42; // error: protected data member
//	d1.m_data_3 = 42; // error: private   data member

	[[maybe_unused]] D2 d2;

//	d2.m_data_1 = 42; // error: protected data member
//	d2.m_data_2 = 42; // error: protected data member
//	d2.m_data_3 = 42; // error: private   data member

	[[maybe_unused]] D3 d3;

//	d3.m_data_1 = 42; // error: private   data member
//	d3.m_data_2 = 42; // error: private   data member
//	d3.m_data_3 = 42; // error: private   data member

	return 0;
}