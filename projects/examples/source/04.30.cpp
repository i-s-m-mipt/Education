///////////////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct remove_reference          { using type = T; };

template < typename T > struct remove_reference < T &  > { using type = T; };

template < typename T > struct remove_reference < T && > { using type = T; };

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T > using  remove_reference_t = typename remove_reference < T > ::type;

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	static_assert(std::is_same_v <      remove_reference_t < int    > , int > );

	static_assert(std::is_same_v <      remove_reference_t < int &  > , int > );

	static_assert(std::is_same_v <      remove_reference_t < int && > , int > );

//  ----------------------------------------------------------------------------

	static_assert(std::is_same_v < std::remove_reference_t < int    > , int > );

	static_assert(std::is_same_v < std::remove_reference_t < int &  > , int > );

	static_assert(std::is_same_v < std::remove_reference_t < int && > , int > );
}

///////////////////////////////////////////////////////////////////////////////////////////