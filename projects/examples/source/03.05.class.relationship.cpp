#include <cassert>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////

class Entity
{
public:

	void test() const
	{
		std::cout << "Entity::test\n";
	}

//  --------------------------------------------

	int data = 0; static inline auto s_data = 0;
};

///////////////////////////////////////////////////////////

struct Client { std::vector < struct Server * > servers; };

struct Server { std::vector < struct Client * > clients; };

///////////////////////////////////////////////////////////

int main()
{
	Entity entity; 

	assert(entity.data == 0 && Entity::s_data == 0);

//  ------------------------------------------------

	auto size = 5uz;

	std::vector < Client > clients(size);
	std::vector < Server > servers(size);
	
	for (auto i = 0uz; i < size; ++i)
	{
		clients[i].servers.push_back(&servers[i]);
		servers[i].clients.push_back(&clients[i]);
	}

//  ------------------------------------------------

	entity.test();
}