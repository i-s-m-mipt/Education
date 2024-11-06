#include <string>

//  ================================================================================================

struct Entity 
{ 
	static inline auto s_data = 0; int data = 0;
};

//  ================================================================================================

struct Client_v1 : public         Entity {};
struct Client_v2 : public virtual Entity {};

struct Server_v1 : public         Entity {}; 
struct Server_v2 : public virtual Entity {};

//  ================================================================================================

struct Router_v1 : public Client_v1, public Server_v1 { Router_v1() {} };
struct Router_v2 : public Client_v2, public Server_v2 { Router_v2() {} };

//  ================================================================================================

int main()
{
	Router_v1 router_v1; // support: compiler-explorer.com

	router_v1.s_data = 1;
//	router_v1.  data = 1; // error

//  ------------------------------------------------------------------------------------------------

	Router_v2 router_v2; // support: compiler-explorer.com

	router_v2.s_data = 1;
	router_v2.  data = 1;

//  ------------------------------------------------------------------------------------------------

	Client_v2 client_v2; // support: compiler-explorer.com
}