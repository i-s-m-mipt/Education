/////////////////////////////////////////////////////////

#include <iostream>
#include <memory>

/////////////////////////////////////////////////////////

class Client
{
public :

   ~Client() 
    { 
		std::cout << "Client::~Client\n";
	}

//  ------------------------------------------

	std::shared_ptr < class Server > m_server;
};

/////////////////////////////////////////////////////////

class Server
{
public :

   ~Server() 
    { 
		std::cout << "Server::~Server\n";
	}

//  ----------------------------------------

	std::weak_ptr < class Client > m_client;
};

/////////////////////////////////////////////////////////

int main()
{
	auto client = std::make_shared < Client > ();

	auto server = std::make_shared < Server > ();

//  ---------------------------------------------
		
	client->m_server           = server;

	client->m_server->m_client = client;
}

/////////////////////////////////////////////////////////