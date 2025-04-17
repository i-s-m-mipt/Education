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

//  ----------------------------------------

	std::shared_ptr < class Server > server;
};

/////////////////////////////////////////////////////////

class Server
{
public :

   ~Server() 
    { 
		std::cout << "Server::~Server\n";
	}

//  --------------------------------------

	std::weak_ptr < class Client > client;
};

/////////////////////////////////////////////////////////

int main()
{
	auto client = std::make_shared < Client > ();

	auto server = std::make_shared < Server > ();

//  ---------------------------------------------
		
	client->server         = server;

	client->server->client = client;
}

/////////////////////////////////////////////////////////