////////////////////////////////////////////////////////

#include <new>
#include <print>

////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) : m_x(x)
	{
		std::print("Entity:: Entity : m_x = {}\n", m_x);
	}

//  ----------------------------------------------------

   ~Entity()
	{
		std::print("Entity::~Entity : m_x = {}\n", m_x);
	}

private :

	int m_x = 0;
};

////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  ---------------------------------------------

    auto x = operator new(sizeof(Entity) * size);

//  ---------------------------------------------

	auto entities = static_cast < Entity * > (x);

//  ---------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		new (&entities[i]) Entity(i + 1);
	}

//  ---------------------------------------------

	entities[0].~Entity();

//  ---------------------------------------------

	new (&entities[0]) Entity(1);

//  ---------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		entities[i].~Entity();
	}

//  ---------------------------------------------

	operator delete(x, sizeof(Entity) * size);
}

////////////////////////////////////////////////////////