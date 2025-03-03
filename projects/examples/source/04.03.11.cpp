#include <type_traits>

///////////////////////////////////////////////////////////////////////////////

template < typename T > class is_pointer         : public std::false_type {};

template < typename T > class is_pointer < T * > : public std:: true_type {};

///////////////////////////////////////////////////////////////////////////////

template < typename T > constexpr auto is_pointer_v = is_pointer < T > ::value;

///////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert( is_pointer_v < int * > );
		
	static_assert(!is_pointer_v < int   > );
}