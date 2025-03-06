#include <iostream>

////////////////////////////////////////////////////////

class Entity
{ 
public:

	virtual ~Entity() = default;

private: 

	void * m_data = nullptr;
};

////////////////////////////////////////////////////////

class Client : public Entity 
{ 
private: 
	
	void * m_data = nullptr;
};

////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity) == 2 * sizeof(void *));

	static_assert(sizeof(Client) == 3 * sizeof(void *));
}