#include <iostream>
#include <string>

[[nodiscard]] inline int get_prvalue()
{
	return 42;
}

[[nodiscard]] inline const int get_const_prvalue()
{
	return 42;
}

/*
[[nodiscard]] inline int && get_xvalue() // warning: returning a reference to a local object
{
	return 42;
}
*/

[[nodiscard]] inline int & get_lvalue()
{
	static int x = 42; return x;
}

[[nodiscard]] inline const int & get_const_lvalue()
{
	static int x = 42; return x;
}

inline void f(      int & ) { std::cout << "      int & " << std::endl; }
inline void f(      int &&) { std::cout << "      int &&" << std::endl; }
inline void f(const int & ) { std::cout << "const int & " << std::endl; }
inline void f(const int &&) { std::cout << "const int &&" << std::endl; }

class Person
{
public:

	Person(const std::string & name) : m_name(name) {}

	[[nodiscard]] const auto & name() const &  { return m_name; } // note: only for lvalue instances
	[[nodiscard]]       auto   name() const && { return m_name; } // note: only for rvalue instances

private:

	std::string m_name;

}; // class Person

[[nodiscard]] inline Person create_person(const std::string & name)
{
	Person person(name); return person;
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