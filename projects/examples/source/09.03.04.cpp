#include <iostream>
#include <new>

/////////////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity(int x) : m_data(x)
	{
		std::cout << "Entity:: Entity : m_data = " << m_data << '\n';
	}

   ~Entity()
	{
		std::cout << "Entity::~Entity : m_data = " << m_data << '\n';
	}

private:

	int m_data = 0;
};

/////////////////////////////////////////////////////////////////////

int main()
{
	auto size = 5uz;

//  -----------------------------------------------

    auto ptr = operator new(sizeof(Entity) * size);

//  -----------------------------------------------

	auto entities = static_cast < Entity * > (ptr);

//  -----------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		new (&entities[i]) Entity(i + 1);
	}

//  -----------------------------------------------

	entities[0].~Entity();

//  -----------------------------------------------

	new (&entities[0]) Entity(1);

//  -----------------------------------------------

	for (auto i = 0uz; i < size; ++i)
	{
		entities[i].~Entity();
	}

//  -----------------------------------------------

	operator delete(ptr, sizeof(Entity) * size);
}