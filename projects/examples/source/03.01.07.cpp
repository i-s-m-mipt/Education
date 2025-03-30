//////////////////////////////////////

#include <cassert>
#include <iostream>

//////////////////////////////////////

class Entity
{
public :

	static void test()
	{
		std::cout << "Entity::test\n";

	//  ------------------------------

	//	m_x = 1; // error
	}

//  ----------------------------------

	static inline       auto s_x = 1;

	static        const auto s_y = 2;

	static inline const auto s_z = 3;

private :

	int m_x = 0;
};

//////////////////////////////////////

int main()
{
	assert(Entity::s_x == 1);

//  -------------------------

	Entity::test();
}

//////////////////////////////////////