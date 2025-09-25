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

	//	++m_x; // error
	}

//  ----------------------------------

	static inline auto       s_x = 1;

	static inline auto const s_y = 2;

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