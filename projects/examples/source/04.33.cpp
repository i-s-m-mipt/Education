//////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <utility>

//////////////////////////////////////////////////////////////////////////////

template < typename D, typename B > class is_convertible
{
private :

    template < typename T > static int test_v1(T);

//  --------------------------------------------------------------------------

	template < typename T1, typename T2 > static std::false_type test_v2(...);

//  --------------------------------------------------------------------------

    template < typename T1, typename T2 > static std:: true_type test_v2
	(
		int, decltype(test_v1 < T2 > (std::declval < T1 > ())) = 0
	);

public :
      
	constexpr static auto value = decltype(test_v2 < D, B > (1))::value;
};

//////////////////////////////////////////////////////////////////////////////

template 
< 
	typename D, typename B 
> 
constexpr auto is_convertible_v = is_convertible < D, B > ::value;

//////////////////////////////////////////////////////////////////////////////

class Entity {};

//////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

//////////////////////////////////////////////////////////////////////////////

class Server 
{ 
public :

	explicit Server(int) {}
};

//////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(     is_convertible_v < int,      double   > == 1);

	static_assert(     is_convertible_v < int,      Server   > == 0);

	static_assert(     is_convertible_v < Client *, Entity * > == 1);

	static_assert(     is_convertible_v < Server *, Entity * > == 0);

//  -----------------------------------------------------------------

	static_assert(std::is_convertible_v < int,      double   > == 1);

	static_assert(std::is_convertible_v < int,      Server   > == 0);

	static_assert(std::is_convertible_v < Client *, Entity * > == 1);

	static_assert(std::is_convertible_v < Server *, Entity * > == 0);
}

//////////////////////////////////////////////////////////////////////////////