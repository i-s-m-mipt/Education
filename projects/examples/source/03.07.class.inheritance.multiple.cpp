#include <cassert>

//  ================================================================================================

class System 
{ 
public: 
	
	static inline const int m_data_1 = 1; 
				  const int m_data_2 = 2; 

}; // class System 

//  ================================================================================================

class Server_v11 : public         System {}; 
class Server_v12 : public virtual System {}; 

class Server_v21 : public         System {}; 
class Server_v22 : public virtual System {}; 

//  ================================================================================================

class Server_v31 : public Server_v11, public Server_v21 { public: Server_v31() {} };
class Server_v32 : public Server_v12, public Server_v22 { public: Server_v32() {} };

//  ================================================================================================

int main()
{
	Server_v31 server_v31; // support: compiler-explorer.com

	assert(server_v31.m_data_1 == 1);
//	assert(server_v31.m_data_2 == 2); // error

//  ================================================================================================

	Server_v32 server_v32; // support: compiler-explorer.com

	assert(server_v32.m_data_1 == 1);
	assert(server_v32.m_data_2 == 2);

//  ================================================================================================

	Server_v22 server_v22; // support: compiler-explorer.com

	return 0;
}