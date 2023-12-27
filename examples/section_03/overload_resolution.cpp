#include <iostream>
#include <string>

int get_prvalue()
{
	return 42;
}

const int get_const_prvalue()
{
	return 42;
}

/*
int && get_xvalue() // warning: returning a reference to a local object
{
	return 42;
}
*/

int & get_lvalue()
{
	static int x = 42;

	return x;
}

const int & get_const_lvalue()
{
	static int x = 42;

	return x;
}

void f([[maybe_unused]] int & arg)
{
	std::cout << "int &" << std::endl;
}

void f([[maybe_unused]] int && arg)
{
	std::cout << "int &&" << std::endl;
}

void f([[maybe_unused]] const int & arg)
{
	std::cout << "const int &" << std::endl;
}

void f([[maybe_unused]] const int && arg)
{
	std::cout << "const int &&" << std::endl;
}

class Person
{
public:

	Person(const std::string & name) : m_name(name) {}

	const auto & name() const &  { return m_name; } // note: only for lvalue instances
	      auto   name() const && { return m_name; } // note: only for rvalue instances

private:

	std::string m_name;

}; // class Person

Person create_person(const std::string & name)
{
	Person person(name);

	return person;
}

int main()
{
	[[maybe_unused]] double d = 0.0;

	const int i = 0;

	f(get_prvalue());
	f(get_const_prvalue()); // note: verify int && overload
	f(get_lvalue());
	f(get_const_lvalue());

	f(0);
//	f(d); // error: ambiguous function overloading 
	f(i);

	Person person("Matthias");

	std::cout << person.name() << std::endl; // note: lvalue version

	std::cout << create_person("Matthias").name() << std::endl; // note: rvalue version
	
	return 0;
}