#include <vector>

//  ================================================================================================

class Client;

//  ================================================================================================

class Server
{
public:

	void connect(const Client * client)
	{
		m_clients.push_back(client);
	}

private:

	std::vector < const Client * > m_clients;

}; // class Server

//  ================================================================================================

class Client
{
public:

	void connect(const Server * server)
	{
		m_servers.push_back(server);
	}

private:

	std::vector < const Server * > m_servers;

}; // class Client

//  ================================================================================================

int main()
{
	const std::size_t size = 5;

	std::vector < Server > servers(size);
	std::vector < Client > clients(size);
	
	for (std::size_t i = 0; i < size; ++i)
	{
		servers[i].connect(&clients[i]);
		clients[i].connect(&servers[i]);
	}

	return 0;
}