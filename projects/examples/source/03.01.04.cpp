//////////////////////////////////////////////////

#include <cassert>
#include <iostream>

//////////////////////////////////////////////////

class Entity
{
public :

	Entity()
    {
        std::cout << "Entity:: Entity (1)\n";
    }

//  ----------------------------------------------

    Entity(int x, int y) : m_x(x), m_y(y)
    {
        std::cout << "Entity:: Entity (2)\n";

    //  -------------------------------------

    //	m_y = y; // error
    }

//  ----------------------------------------------

//	Entity(int x, int y) : m_y(x), m_x(y) // error
//  {
//      std::cout << "Entity:: Entity (3)\n";
//  }

//  ----------------------------------------------

	Entity(int x) : Entity(x, 0)
	{
        std::cout << "Entity:: Entity (4)\n";
	}

//  ----------------------------------------------

   ~Entity()
    {
        std::cout << "Entity::~Entity\n";
    }

private :

    int       m_x = 0;
          
    int const m_y = 0;
};

//////////////////////////////////////////////////

int main()
{
    Entity entity_1;

//	Entity entity_2(); // error

	Entity entity_3(3, 3);
	
	Entity entity_4(4);

//  -----------------------------------

//	assert(entity_1.m_x == 0); // error
}

//////////////////////////////////////////////////