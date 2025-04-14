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

	static inline auto       s_x = 1;

	static        auto const s_y = 2;

	static inline auto const s_z = 3;

private :

	int m_x = 0;
};

//////////////////////////////////////

int main()
{
	Entity::test();

//  -------------------------

	assert(Entity::s_x == 1);
}

//////////////////////////////////////