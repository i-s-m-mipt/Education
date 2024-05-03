#include <iostream>
#include <string>

//  ================================================================================================

[[nodiscard]] inline       int    get_prvalue      () { return 42; }
/*
[[nodiscard]] inline       int && get__xvalue      () { return 42; } // warning: dangling reference
*/
[[nodiscard]] inline       int &  get__lvalue      () { static       int x = 42; return x; }
[[nodiscard]] inline const int &  get__lvalue_const() { static const int x = 42; return x; }

//  ================================================================================================

inline void f(      int & ) { std::cout << "f(      int & )" << std::endl; }
inline void f(      int &&) { std::cout << "f(      int &&)" << std::endl; }
inline void f(const int & ) { std::cout << "f(const int & )" << std::endl; }
inline void f(const int &&) { std::cout << "f(const int &&)" << std::endl; }

//  ================================================================================================

class Person
{
public:

	Person(const std::string & name) : m_name(name) {}

	[[nodiscard]] const std::string & name() const &  { return m_name; } // note: for lvalue only
	[[nodiscard]]       std::string   name() const && { return m_name; } // note: for rvalue only

private:

	const std::string m_name;

}; // class Person

//  ================================================================================================

[[nodiscard]] inline Person create_person(const std::string & name)
{
	const Person person(name); return person;
}

//  ================================================================================================

int main()
{
	f(get_prvalue      ());
	f(get__lvalue      ());
	f(get__lvalue_const());

//  ================================================================================================

	[[maybe_unused]] double d = 3.14;

	const int i = 42;

//	f(d); // error: ambiguous function overloading 

	f(i);

//  ================================================================================================

	const Person person("Matthias");

	std::cout << person.name() << std::endl; // note: lvalue version

	std::cout << create_person("Matthias").name() << std::endl; // note: rvalue version
	
	return 0;
}