#include <iostream>

////////////////////////////////////////////////////

class Entity
{
public:

	Entity(int x) : m_data(x) {}

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

////////////////////////////////////////////////////

struct Client { struct Server * server = nullptr; };

struct Server { struct Client * client = nullptr; };

////////////////////////////////////////////////////

int main()
{
	Entity entity_1(1), entity_2(2);

//  --------------------------------

	Entity::s_data = 1;

//  --------------------------------

	Client client;

	Server server;

	server.client = &client;

	client.server = &server;

//  --------------------------------

	Entity::test();
}