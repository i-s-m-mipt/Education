#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

//  ================================================================================================

class Person_v1
{
public:
	
	explicit Person_v1(const std::string & name) : m_name(name) 
	{
		std::cout << "Person_v1::Person_v1 (copy)" << std::endl;
	}

	explicit Person_v1(std::string && name) : m_name(std::move(name)) 
	{
		std::cout << "Person_v1::Person_v1 (move)" << std::endl;
	}
	
	Person_v1(const Person_v1 &  other) : m_name(          other.m_name ) {}
	Person_v1(      Person_v1 && other) : m_name(std::move(other.m_name)) {}

private:

	std::string m_name;

}; // class Person_v1

//  ================================================================================================

class Person_v2
{
public:
	
    template < typename S > explicit Person_v2(S && name) : m_name(std::forward < S > (name)) 
	{
		std::cout << "Person_v2::Person_v2" << std::endl;
	}
	
	Person_v2(const Person_v2 &  other) : m_name(          other.m_name ) {}
	Person_v2(      Person_v2 && other) : m_name(std::move(other.m_name)) {}

private:

	std::string m_name;

}; // class Person_v2

//  ================================================================================================

class Person_v3
{
public:
	
    template < typename S, typename Enable = std::enable_if_t <

		std::is_convertible_v < S, std::string > , void > > 

	explicit Person_v3(S && name) : m_name(std::forward < S > (name)) // good: SFINAE idiom
	{
		std::cout << "Person_v3::Person_v3" << std::endl;
	}
	
	Person_v3(const Person_v3 &  other) : m_name(          other.m_name ) {}
	Person_v3(      Person_v3 && other) : m_name(std::move(other.m_name)) {}

private:

	std::string m_name;

}; // class Person_v3

//  ================================================================================================

class Person_v4
{
public:
	
    template < typename S > requires std::is_convertible_v < S, std::string >
	
	explicit Person_v4(S && name) : m_name(std::forward < S > (name)) // good: requires-clause
	{
		std::cout << "Person_v4::Person_v4" << std::endl;
	}
	
	Person_v4(const Person_v4 &  other) : m_name(          other.m_name ) {}
	Person_v4(      Person_v4 && other) : m_name(std::move(other.m_name)) {}

private:

	std::string m_name;

}; // class Person_v4

//  ================================================================================================

int main()
{
	const auto name = "Matthias";

	Person_v1 person_v1_1(                 name ); // note: main constructor with copy
	Person_v1 person_v1_2(           "Matthias" ); // note: main constructor with move
	Person_v1 person_v1_3(          person_v1_1 ); // note: copy constructor
	Person_v1 person_v1_4(std::move(person_v1_1)); // note: move constructor

    Person_v2 person_v2_1(                 name ); // note: template constructor with copy
	Person_v2 person_v2_2(           "Matthias" ); // note: template constructor with move

//	Person_v2 person_v2_3(person_v2_1); // error: template constructor instead of copy constructor

    const Person_v2 person_v2_4(name); // note: const required for copy constructor call

    Person_v2 person_v2_5(          person_v2_4 ); // note: copy constructor 
	Person_v2 person_v2_6(std::move(person_v2_1)); // note: move constructor

	Person_v3 person_v3_1(                 name ); // note: template constructor with copy
	Person_v3 person_v3_2(           "Matthias" ); // note: template constructor with move
	Person_v3 person_v3_3(          person_v3_1 ); // note: copy constructor
	Person_v3 person_v3_4(std::move(person_v3_1)); // note: move constructor

	Person_v4 person_v4_1(                 name ); // note: template constructor with copy
	Person_v4 person_v4_2(           "Matthias" ); // note: template constructor with move
	Person_v4 person_v4_3(          person_v4_1 ); // note: copy constructor
	Person_v4 person_v4_4(std::move(person_v4_1)); // note: move constructor

	return 0;
}