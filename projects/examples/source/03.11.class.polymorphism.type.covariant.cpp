#include <iostream>

//  ================================================================================================

class System_v1 
{
public:

	virtual ~System_v1() = default;

}; // class System_v1 

class Server_v1 : public System_v1 {};

//  ================================================================================================

class System_v2 
{
public:

	virtual ~System_v2() = default;

	[[nodiscard]] virtual const System_v1 * test() const 
	{ 
		std::clog << "System_v2::test\n";

		return new const System_v1(); 
	}

}; // class System_v2

//  ================================================================================================

class Server_v2 : public System_v2
{
public:

	[[nodiscard]] const Server_v1 * test() const override 
	{ 
		std::clog << "Server_v2::test\n";

		return new const Server_v1(); 
	}

}; // class Server_v2 : public System_v2

//  ================================================================================================

int main()
{
	const System_v2 * const system_v2 = new const Server_v2();

	delete system_v2->test();

	delete system_v2;

	return 0;
}