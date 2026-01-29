//////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

//////////////////////////////////////////////////////////////

// section : User-Defined Data Types

//////////////////////////////////////////////////////////////

// content : Classes
//
// content : Declaration class
//
// content : Encapsulation
//
// content : Access Specifiers public and private
//
// content : Default, Used-Defined and Delegating Constructors
//
// content : Initializer Lists
//
// content : The Most Vexing Parse
//
// content : Destructors

//////////////////////////////////////////////////////////////

#include <cassert>
#include <print>

//////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity()
    {
        std::print("Entity:: Entity (1)\n");
    }

//  ----------------------------------------------

    Entity(int x, int y) : m_x(x), m_y(y)
    {
        std::print("Entity:: Entity (2)\n");

    //	m_y = y; // error
    }

//  ----------------------------------------------

//	Entity(int x, int y) : m_y(y), m_x(x) // error
//  {
//      std::print("Entity:: Entity (3)\n");
//  }

//  ----------------------------------------------

	Entity(int x) : Entity(x, 0)
	{
        std::print("Entity:: Entity (4)\n");
	}

//  ----------------------------------------------

   ~Entity()
    {
        std::print("Entity::~Entity\n");
    }

private :

    int       m_x = 0;
          
    int const m_y = 0;
};

//////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1;

//	Entity entity_2(); // error

	Entity entity_3(3, 3);
	
	Entity entity_4(4);

//  -----------------------------------

//	assert(entity_1.m_x == 0); // error
}

//////////////////////////////////////////////////////////////