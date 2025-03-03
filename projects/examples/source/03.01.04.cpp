#include <iostream>

///////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity()
    {
        std::cout << "Entity:: Entity (1)\n";
    }

//  -----------------------------------------------------------

//	Entity(int x, int y) : m_data_2(x), m_data_1(y) {} // error

    Entity(int x, int y) : m_data_1(x), m_data_2(y)
    {
        std::cout << "Entity:: Entity (2)\n";

//		m_data_2 = y; // error
    }

//  -----------------------------------------------------------

	Entity(int x) : Entity(x, 0) 
	{
        std::cout << "Entity:: Entity (3)\n";
	}

//  -----------------------------------------------------------

   ~Entity()
    {
        std::cout << "Entity::~Entity\n";
    }

private:

    int m_data_1 = 0; const int m_data_2 = 0;
};

///////////////////////////////////////////////////////////////

int main()
{
    Entity entity_1;

//	Entity entity_2(); // error

	Entity entity_3(3, 3);
	
	Entity entity_4(4);
}