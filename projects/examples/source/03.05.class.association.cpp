#include <vector>

//  ================================================================================================

class Client
{
public:

	void add_server(class Server * server)
	{
		m_servers.push_back(server);
	}

private:

	std::vector < class Server * > m_servers;
};

//  ================================================================================================

class Server
{
public:

	void add_client(Client * client)
	{
		m_clients.push_back(client);
	}

private:

	std::vector < Client * > m_clients;
};

//  ================================================================================================

int main()
{
	auto size = 5uz;

	std::vector < Client > clients(size);
	std::vector < Server > servers(size);
	
	for (auto i = 0uz; i < size; ++i)
	{
		clients[i].add_server(&servers[i]);
		servers[i].add_client(&clients[i]);
	}
}