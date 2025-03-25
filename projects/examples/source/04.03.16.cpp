#include <cstdint>

///////////////////////////////////////////////////////////////////////////////////

template < typename D, typename B > class is_derived
{
private :

	static std::int32_t test(...);

	static std::int64_t test(B *);

public :

	static constexpr auto value = sizeof(test(static_cast < D * > (nullptr))) == 8;
};

///////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename D, typename B 
> 
constexpr auto is_derived_v = is_derived < D, B > ::value;

///////////////////////////////////////////////////////////////////////////////////

class Entity {};

class Client : public Entity {};

class Server {};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(is_derived_v < Client, Entity > == 1);

	static_assert(is_derived_v < Server, Entity > == 0);

//	static_assert(is_derived_v < Client, Client > == 1); // bad
}