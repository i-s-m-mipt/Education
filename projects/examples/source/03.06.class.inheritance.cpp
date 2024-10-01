#include <cassert>
#include <iostream>
#include <string>

//  ================================================================================================

class System
{
public:

	System(const std::string & name) : m_name(name) {}

public:

	void test_v1() const { std::clog << "System::test_v1\n"; }
	void test_v2() const { std::clog << "System::test_v2\n"; }

protected:

	[[nodiscard]] const std::string & get_name() const 
	{ 
		return m_name; 
	}

private:

	const std::string m_name;

}; // class System

//  ================================================================================================

class Server : public System
{
public:

	Server(const std::string & name, int data) : System(name), m_data(data)
	{
		assert(get_name() == name);
	}

public:

	void test_v1() const
	{
		std::clog << "Server::test_v1\n";

//		test_v1(); // error

		System::test_v1();
	}

	using System::get_name;

private:

	const int m_data = 0;

}; // class Server : public System

//  ================================================================================================

class Client_v1 : private System 
{
public:

	Client_v1(const std::string & name) : System(name) {}

public:

	void test() const 
	{ 
		test_v1(); 
		test_v2(); 
	}

}; // class Client_v1 : private System 

//  ================================================================================================

class Client_v2 
{
public:

	Client_v2(const std::string & name) : m_system(name) {}

public:

	void test() const 
	{ 
		m_system.test_v1(); 
		m_system.test_v2(); 
	}

private: 

	const System m_system; 

}; // class Client_v2

//  ================================================================================================

int main()
{
	const System system("system");

//	const auto system_name = system.get_name(); // error

//  ================================================================================================

	const Server server("server", 1);

	server.test_v1();
	server.test_v2();

	const auto server_name = server.get_name();

//  ================================================================================================

	Client_v1 client_v1("client_v1");
	
//	client_v1.test_v1(); // error
//	client_v1.test_v2(); // error

	client_v1.test();

//  ================================================================================================

	Client_v2 client_v2("client_v2");

	client_v2.test();

	return 0;
}