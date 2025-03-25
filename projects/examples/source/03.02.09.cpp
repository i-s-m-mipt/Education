// support : Boost.CompressedPair

///////////////////////////////////////////////////////////////////////////////////////

class Entity_v1 {};

class Entity_v2 { public : char x = '\0';                       Entity_v1 entity_v1; };

class Entity_v3 { public : char x = '\0'; [[no_unique_address]] Entity_v1 entity_v1; };

///////////////////////////////////////////////////////////////////////////////////////

class Client_v1 : public 		 Entity_v1 {};

class Client_v2 : public virtual Entity_v1 {};

class Server_v1 : public 		 Entity_v1 {};

class Server_v2 : public virtual Entity_v1 {};

///////////////////////////////////////////////////////////////////////////////////////

class Router_v1 : public Client_v1, public Server_v1 {};

class Router_v2 : public Client_v2, public Server_v2 {};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(sizeof(Entity_v1) == 1);

	static_assert(sizeof(Entity_v2) == 2);

	static_assert(sizeof(Entity_v3) == 1);

//  --------------------------------------

	static_assert(sizeof(Router_v1) == 2);

	static_assert(sizeof(Router_v2) != 1);
}