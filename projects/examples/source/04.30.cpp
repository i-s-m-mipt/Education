///////////////////////////////////////////////////////////////////////////////////////////////////

#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > struct add_lvalue_reference { using type = T &;  };

template < typename T > struct add_rvalue_reference { using type = T &&; };

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T > using  add_lvalue_reference_t = typename add_lvalue_reference < T > ::type;

template < typename T > using  add_rvalue_reference_t = typename add_rvalue_reference < T > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::is_same_v <      add_lvalue_reference_t < int > , int &  > );

	static_assert(std::is_same_v <      add_rvalue_reference_t < int > , int && > );

//  --------------------------------------------------------------------------------

    static_assert(std::is_same_v < std::add_lvalue_reference_t < int > , int &  > );

	static_assert(std::is_same_v < std::add_rvalue_reference_t < int > , int && > );
}

///////////////////////////////////////////////////////////////////////////////////////////////////