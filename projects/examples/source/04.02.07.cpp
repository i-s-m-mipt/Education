//////////////////////////////////////////////////////////////////////////////////////////////////

#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

//////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std::literals;

//////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v1
{
public :
	
	Entity_v1(std::string const & string) : m_string(string) 
	{
		std::cout << "Entity_v1::Entity_v1 (1)\n";
	}

//  -------------------------------------------------------------------

	Entity_v1(std::string && string) : m_string(std::move(string)) 
	{
		std::cout << "Entity_v1::Entity_v1 (2)\n";
	}

//  -------------------------------------------------------------------
	
	Entity_v1(Entity_v1 const & other) : m_string(other.m_string) 
	{
		std::cout << "Entity_v1::Entity_v1 (3)\n";
	}

//  -------------------------------------------------------------------

	Entity_v1(Entity_v1 && other) : m_string(std::move(other.m_string)) 
	{
		std::cout << "Entity_v1::Entity_v1 (4)\n";
	}

private :

	std::string m_string;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v2
{
public :
	
    template < typename S > Entity_v2(S && string) : m_string(std::forward < S > (string))
	{
		std::cout << "Entity_v2::Entity_v2 (1)\n";
	}

//  --------------------------------------------------------------------------------------
	
	Entity_v2(Entity_v2 const & other) : m_string(other.m_string) 
	{
		std::cout << "Entity_v2::Entity_v2 (2)\n";
	}

//  --------------------------------------------------------------------------------------

	Entity_v2(Entity_v2 && other) : m_string(std::move(other.m_string)) 
	{
		std::cout << "Entity_v2::Entity_v2 (3)\n";
	}

private :

	std::string m_string;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v3
{
public :
	
    template 
	< 
		typename S, typename = std::enable_if_t 
		< 
			std::convertible_to < S, std::string > , void 
		> 
	>
	Entity_v3(S && string) : m_string(std::forward < S > (string))
	{
		std::cout << "Entity_v3::Entity_v3 (1)\n";
	}

//  -------------------------------------------------------------------
	
	Entity_v3(Entity_v3 const & other) : m_string(other.m_string) 
	{
		std::cout << "Entity_v3::Entity_v3 (2)\n";
	}

//  -------------------------------------------------------------------

	Entity_v3(Entity_v3 && other) : m_string(std::move(other.m_string)) 
	{
		std::cout << "Entity_v3::Entity_v3 (3)\n";
	}

private :

	std::string m_string;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

class Entity_v4
{
public :
	
    template < typename S > Entity_v4(S && string) requires std::convertible_to < S, std::string >
	: 
		m_string(std::forward < S > (string))
	{
		std::cout << "Entity_v4::Entity_v4 (1)\n";
	}

//  ----------------------------------------------------------------------------------------------
	
	Entity_v4(Entity_v4 const & other) : m_string(other.m_string) 
	{
		std::cout << "Entity_v4::Entity_v4 (2)\n";
	}

//  ----------------------------------------------------------------------------------------------

	Entity_v4(Entity_v4 && other) : m_string(std::move(other.m_string)) 
	{
		std::cout << "Entity_v4::Entity_v4 (3)\n";
	}

private :

	std::string m_string;
};

//////////////////////////////////////////////////////////////////////////////////////////////////

template < typename E > void test()
{
	auto string = "aaaaa"s;

	E entity_1(string);

	E entity_2("aaaaa"s);

	E entity_3 = entity_2;

	E entity_4 = std::move(entity_3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	test < Entity_v1 > ();

//	test < Entity_v2 > (); // error

	test < Entity_v3 > ();

	test < Entity_v4 > ();

//  ---------------------------------------------

	Entity_v2       entity_v2_1("aaaaa"s);

	Entity_v2 const entity_v2_2("aaaaa"s);

//  ---------------------------------------------

//	Entity_v2 entity_v2_3 = entity_v2_1; // error

	Entity_v2 entity_v2_4 = entity_v2_2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////