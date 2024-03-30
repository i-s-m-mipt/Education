#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// =================================================================================================

class Person_v1
{
public:
	
	explicit Person_v1(const std::string & name) : m_name(name) 
	{
		std::cout << "constructor (main) / copy" << std::endl;
	}

	explicit Person_v1(std::string && name) : m_name(std::move(name)) 
	{
		std::cout << "constructor (main) / move" << std::endl;
	}
	
	Person_v1(const Person_v1 & other) : m_name(other.m_name)
	{
		std::cout << "constructor (copy)" << std::endl;
	}

	Person_v1(Person_v1 && other) : m_name(std::move(other.m_name)) 
	{
		std::cout << "constructor (move)" << std::endl;
	}

private:

	std::string m_name;

}; // class Person_v1

// =================================================================================================

class Person_v2
{
public:
	
    template < typename S > explicit Person_v2(S && name) : m_name(std::forward < S > (name)) 
	{
		std::cout << "constructor (template)" << std::endl;
	}
	
	Person_v2(const Person_v2 & other) : m_name(other.m_name)
	{
		std::cout << "constructor (copy)" << std::endl;
	}

	Person_v2(Person_v2 && other) : m_name(std::move(other.m_name)) 
	{
		std::cout << "constructor (move)" << std::endl;
	}

private:

	std::string m_name;

}; // class Person_v2

// =================================================================================================



// =================================================================================================

int main()
{
	const std::string name = "Matthias";

	Person_v1 person_v1_1(                 name ); // note: main constructor with copy
	Person_v1 person_v1_2(           "Matthias" ); // note: main constructor with move
	Person_v1 person_v1_3(          person_v1_1 ); // note: copy constructor
	Person_v1 person_v1_4(std::move(person_v1_1)); // note: move constructor

    Person_v2 person_v2_1(                 name ); // note:  template constructor with copy
	Person_v2 person_v2_2(           "Matthias" ); // note:  template constructor with move

//	Person_v2 person_v2_3(          person_v2_1 ); // error: template constructor instead of copy constructor

    const Person_v2 person_v2_4(name); // note: const required for copy constructor call

    Person_v2 person_v2_5(          person_v2_4 ); // note: copy constructor 
	Person_v2 person_v2_6(std::move(person_v2_1)); // note: move constructor

	return 0;
}