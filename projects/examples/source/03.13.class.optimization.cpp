struct Entity_v1 {}; // support: boost::compressed_pair

struct Entity_v2 { char c = '\0';                       Entity_v1 entity_v1; };

struct Entity_v3 { char c = '\0'; [[no_unique_address]] Entity_v1 entity_v1; };

struct Entity_v4 { char c = '\0'; [[no_unique_address]] Entity_v1 entity_v1_1, entity_v1_2; };

//  ================================================================================================

struct Client : public Entity_v1 {};

struct Server : public Entity_v1 {};

struct Router : public Client, public Server {};

//  ================================================================================================

int main()
{
	static_assert(sizeof(Entity_v1) == 1);
	static_assert(sizeof(Entity_v2) == 2);
	static_assert(sizeof(Entity_v3) == 1);
	static_assert(sizeof(Entity_v4) == 2);

//  --------------------------------------

	static_assert(sizeof(Client) == 1);
	static_assert(sizeof(Server) == 1);	
	static_assert(sizeof(Router) == 2);
}