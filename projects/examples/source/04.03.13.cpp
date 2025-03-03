#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_lvalue_reference          : public std::false_type {};

template < typename T > class is_lvalue_reference < T &  > : public std:: true_type {};

///////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T 
> 
constexpr auto is_lvalue_reference_v = is_lvalue_reference < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////

template < typename T > class is_rvalue_reference          : public std::false_type {};

template < typename T > class is_rvalue_reference < T && > : public std:: true_type {};

///////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T 
> 
constexpr auto is_rvalue_reference_v = is_rvalue_reference < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(!is_lvalue_reference_v < int    > );

    static_assert( is_lvalue_reference_v < int &  > );

    static_assert(!is_lvalue_reference_v < int && > );

//  --------------------------------------------------

    static_assert(!is_rvalue_reference_v < int    > );

    static_assert(!is_rvalue_reference_v < int &  > );

    static_assert( is_rvalue_reference_v < int && > );
}