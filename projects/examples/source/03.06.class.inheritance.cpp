#include <iostream>
#include <string>

//  ================================================================================================

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

	[[nodiscard]] const std::string & get_name() const { return m_name; }

private:

	const std::string m_name;

}; // class Person

//  ================================================================================================

class Employee : public Person
{
public:

	Employee(const std::string & name, int salary) : Person(name), m_salary(salary)
	{
		std::cout << "Employee::Employee " << name << std::endl;

//		std::cout << m_name << std::endl; // error

		std::cout << get_name() << std::endl;
	}

public:

	void print() const
	{
		std::cout << "Employee::print" << std::endl;

//		print(); // error

		Person::print();
	}

	using Person::get_name;

private:

	const int m_salary;

}; // class Employee : public Person

//  ================================================================================================

class Manager : public Employee
{
public:

	Manager(const std::string & name, int salary, char mark) : Employee(name, salary), m_mark(mark)
	{
		std::cout << "Manager::Manager " << name << std::endl;
	}

public:

	void print() const { std::cout << "Manager::print" << std::endl; }

private:

	const char m_mark;

}; // class Manager : public Employee

//  ================================================================================================

class Servo {};

class Robot_v1 : private Servo {};

class Robot_v2 { private: const Servo m_servo; };

//  ================================================================================================

class Base
{
public:    int m_data_1{};
protected: int m_data_2{}; 
private:   int m_data_3{}; 

}; // class Base

//  ================================================================================================

class Derived_1 : public Base
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error
	}

}; // class Derived_1 : public Base

//  ================================================================================================

class Derived_2 : protected Base
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error
	}

}; // class Derived_2 : protected Base

//  ================================================================================================

class Derived_3 : private Base
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error
	}

}; // class Derived_3 : private Base

//  ================================================================================================

int main()
{
	const Person person("Matthias");

//	const auto person_name = person.get_name(); // error

//  ================================================================================================

	const Employee employee("Matthias", 100'000);

	employee.print();

	const auto employee_name = employee.get_name();

//  ================================================================================================

	const Manager manager("Matthias", 100'000, 10);

	manager.print_person();

//  ================================================================================================

	Derived_1 derived_1;
	Derived_2 derived_2;
	Derived_3 derived_3;

	derived_1.m_data_1 = 42;
//	derived_1.m_data_2 = 42; // error
//	derived_1.m_data_3 = 42; // error

//	derived_2.m_data_1 = 42; // error
//	derived_2.m_data_2 = 42; // error
//	derived_2.m_data_3 = 42; // error

//	derived_3.m_data_1 = 42; // error
//	derived_3.m_data_2 = 42; // error
//	derived_3.m_data_3 = 42; // error

	return 0;
}