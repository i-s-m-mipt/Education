#include <cassert>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////

class Entity
{
public:

	Entity() = default;

	Entity(int data) : m_data(data) {}

//  ----------------------------------

	static void test()
	{
		std::cout << "Entity::test\n";
	}

//  ----------------------------------

	static inline auto s_data = 0;

private:

	int m_data = 0; 
};

///////////////////////////////////////////////////////////

struct Client { std::vector < struct Server * > servers; };

struct Server { std::vector < struct Client * > clients; };

///////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity_1(1), entity_2(2);
	}
	
//  --------------------------------------------------

	{
		Entity::s_data = 1;
	}

//  --------------------------------------------------

	{
		auto size = 5uz;

		std::vector < Client > clients(size);

		std::vector < Server > servers(size);
		
		for (auto i = 0uz; i < size; ++i)
		{
			clients[i].servers.push_back(&servers[i]);

			servers[i].clients.push_back(&clients[i]);
		}
	}

//  --------------------------------------------------

	{
		Entity::test();
	}
}