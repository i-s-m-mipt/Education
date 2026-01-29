///////////////////////////////////////////

// chapter : Object-Oriented Programming

///////////////////////////////////////////

// section : User-Defined Data Types

///////////////////////////////////////////

// content : Static Data Members
//
// content : Storage Class Specifier static
//
// content : Inline Variables
//
// content : Variable Specifier inline
//
// content : Static Member Functions
//
// content : Function Specifier static

///////////////////////////////////////////

#include <cassert>
#include <print>

///////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x) {}

//  ------------------------------------

	void test_v1() const
	{
		std::print("Entity::test_v1\n");

		++s_y;
	}

//  ------------------------------------

	static void test_v2()
	{
		std::print("Entity::test_v2\n");

	//	++m_x; // error
	}

//  ------------------------------------

//	static        auto s_x = 1; // error

	static inline auto s_y = 2;

private :

	int m_x = 0;
};

///////////////////////////////////////////

int main()
{
	Entity entity(1);

//  -------------------------

	assert(Entity::s_y == 2);

//  -------------------------

	entity.test_v1();

//  -------------------------

	assert(Entity::s_y == 3);

//  -------------------------

	Entity::test_v2();
}

///////////////////////////////////////////