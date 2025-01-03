class Entity 
{ 
public: 

	int data = 0; static inline auto s_data = 0;
};

////////////////////////////////////////////////////////////////////////////////

class Client_v1 : public         Entity {};
class Client_v2 : public virtual Entity {};

class Server_v1 : public         Entity {}; 
class Server_v2 : public virtual Entity {};

////////////////////////////////////////////////////////////////////////////////

class Router_v1 : public Client_v1, public Server_v1 { public: Router_v1() {} };
class Router_v2 : public Client_v2, public Server_v2 { public: Router_v2() {} };

////////////////////////////////////////////////////////////////////////////////

int main()
{
	Router_v1 router_v1; // support: compiler-explorer.com

	router_v1.s_data = 1;
//	router_v1.  data = 1; // error

//  ------------------------------------------------------

	Router_v2 router_v2; // support: compiler-explorer.com

	router_v2.s_data = 1;
	router_v2.  data = 1;

//  ------------------------------------------------------

	Client_v2 client_v2; // support: compiler-explorer.com
}