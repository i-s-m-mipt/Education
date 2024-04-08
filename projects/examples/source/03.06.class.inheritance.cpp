#include <iostream>
#include <string>

// =================================================================================================

class Person
{
public:

	Person(const std::string & name) : m_name(name)
	{
		std::cout << "Person::Person " << name << std::endl;
	}

public:

	void print       () const { std::cout << "Person::print       " << std::endl; }
	void print_person() const { std::cout << "Person::print_person" << std::endl; }

protected:

	[[nodiscard]] const std::string & get_name() const // good: return by constant reference
	{
		return m_name;
	}

private:

	const std::string m_name;

}; // class Person

// =================================================================================================

class Employee : public Person // good: Employee is a variety of Person
{
public:

	Employee(const std::string & name, int salary) : Person(name), m_salary(salary)
	{
		std::cout << "Employee::Employee " << name << std::endl;

//		std::cout << m_name << std::endl; // error: private member of base class

		std::cout << get_name() << std::endl;
	}

public:

	void print() const // note: avoid inherited non-virtual functions redefinition
	{
		std::cout << "Employee::print" << std::endl;

//		print(); // error: infinite recursion

		Person::print();
	}

	using Person::get_name; // note: change access specifier to public

private:

	const int m_salary;

}; // class Employee : public Person

// =================================================================================================

class Manager : public Employee // good: Manager is a variety of Employee
{
public:

	Manager(const std::string & name, int salary, int level) : Employee(name, salary), m_level(level)
	{
		std::cout << "Manager::Manager " << name << std::endl;
	}

public:

	void print() const { std::cout << "Manager::print" << std::endl; }

private:

	const int m_level;

}; // class Manager : public Employee

// =================================================================================================

class Servo {};

class Robot // : private Servo // bad: Robot is implemented through Servo
{
private:

	const Servo m_servo; // good: prefer composition instead of private inheritance

}; // class Robot

// =================================================================================================

class Base
{
public:    int m_data_1{}; // note: avoid public data mostly
protected: int m_data_2{}; // note: use protected data by situation
private:   int m_data_3{}; // good: prefer private data in hierarchies

}; // class Base

// =================================================================================================

class Derived_1 : public Base // note: useful inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_1 : public Base

// =================================================================================================

class Derived_2 : protected Base // note: useless inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_2 : protected Base

// =================================================================================================

class Derived_3 : private Base // note: default inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_3 : private Base

// =================================================================================================

int main()
{
	const Person person("Matthias");

//	const auto person_name = person.get_name(); // error: protected member function

	const Employee employee("Matthias", 100'000);

	employee.print();

	[[maybe_unused]] const auto employee_name = employee.get_name();

	const Manager manager("Matthias", 100'000, 10);

	manager.print_person();

	Derived_1 derived_1;

	derived_1.m_data_1 = 42;
//	derived_1.m_data_2 = 42; // error: protected data member
//	derived_1.m_data_3 = 42; // error: private   data member

	Derived_2 derived_2;

//	derived_2.m_data_1 = 42; // error: protected data member
//	derived_2.m_data_2 = 42; // error: protected data member
//	derived_2.m_data_3 = 42; // error: private   data member

	Derived_3 derived_3;

//	derived_3.m_data_1 = 42; // error: private   data member
//	derived_3.m_data_2 = 42; // error: private   data member
//	derived_3.m_data_3 = 42; // error: private   data member

	return 0;
}