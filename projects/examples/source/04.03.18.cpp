#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////

template < typename B > class is_polymorphic
{
private :

	template < typename T > static std::false_type test(...);

    template < typename T > static std:: true_type test
	(
		int, decltype(dynamic_cast < void * > (std::declval < T * > ())) = nullptr
	);

public :
      
	static constexpr auto value = decltype(test < B > (1))::value;
};

///////////////////////////////////////////////////////////////////////////////////////

template < typename B > constexpr auto is_polymorphic_v = is_polymorphic < B > ::value;

///////////////////////////////////////////////////////////////////////////////////////

class Entity 
{ 
public :

	virtual ~Entity() = default;
};

///////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

class Server {};

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(     is_polymorphic_v < Entity > == 1);

	static_assert(     is_polymorphic_v < Client > == 1);

	static_assert(     is_polymorphic_v < Server > == 0);

//  -----------------------------------------------------

	static_assert(std::is_polymorphic_v < Entity > == 1);

	static_assert(std::is_polymorphic_v < Client > == 1);

	static_assert(std::is_polymorphic_v < Server > == 0);
}