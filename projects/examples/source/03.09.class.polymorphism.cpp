#include <iostream>
#include <vector>

//  ================================================================================================

class System 
{
public:

	System()
	{
//		test_v1(); // bad
	}

// ~System() = default; // error

	virtual ~System() = default;

public:

	virtual void test_v1() const 
	{ 
		std::clog << "System::test_v1\n"; 
	}

	virtual void test_v2() const = 0;

//	virtual void test_v3() const = 0 // error
//	{
//		std::clog << "System::test_v3\n";
//	}

private:

	const int * m_system_data = nullptr;

}; // class System

void System::test_v2() const 
{ 
	std::clog << "System::test_v2\n"; 
}

//  ================================================================================================

class Server : public System
{
public:

	void test_v1() const override final 
	{ 
		std::clog << "Server::test_v1\n"; 
	}

	void test_v2() const override 
	{ 
		std::clog << "Server::test_v2\n"; 

		System::test_v2();
	}

private:

	const int * m_server_data = nullptr;

}; // class Server final : public System

//  ================================================================================================

class Client final : public System 
{
public:

	void test_v2() const override 
	{ 
		std::clog << "Client::test_v2\n"; 

		System::test_v2();
	}

private:

	const int * m_client_data = nullptr;

}; // class Client final : public System 

//  ================================================================================================

int main()
{
	const Server server;

	[[maybe_unused]] const System * system_1 = &server;
	[[maybe_unused]] const System & system_2 =  server;
//	[[maybe_unused]] const System   system_3 =  server; // error

	system_1->test_v1(); // support: compiler-explorer.com

//  ================================================================================================

	std::vector < const System * > systems 
	{ 
		new const Server(), 
		new const Client() 
	};

	for (const auto system : systems) 
	{
		system->test_v1();
		system->test_v2();

		delete system;
	}

//  ================================================================================================

	std::cout << "sizeof(System) = " << sizeof(System) << '\n';
	std::cout << "sizeof(Server) = " << sizeof(Server) << '\n';
	std::cout << "sizeof(Client) = " << sizeof(Client) << '\n';

	return 0;
}