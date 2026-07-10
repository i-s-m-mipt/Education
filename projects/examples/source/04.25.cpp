///////////////////////////////////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

///////////////////////////////////////////////////////////////////////////////////////////////////

// content : Type Lists
//
// content : Library Boost.Mp11

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <boost/mp11.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Deque {};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto  size_v = boost::mp11:: mp_size < D > ::value;

template < typename D > constexpr auto empty_v = boost::mp11::mp_empty < D > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D             > using      front = boost::mp11::     mp_front < D    > ;

template < typename D, typename T > using push_front = boost::mp11::mp_push_front < D, T > ;

template < typename D             > using  pop_front = boost::mp11:: mp_pop_front < D    > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D             > using       back = boost::mp11::      mp_back < D    > ;

template < typename D, typename T > using  push_back = boost::mp11:: mp_push_back < D, T > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_back = boost::mp11::mp_take_c < D, size_v < D > - 1 > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, std::size_t I > using at = boost::mp11::mp_at_c < D, I > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template
<
    typename T1, typename T2 
>
using Comparator = std::integral_constant < bool, sizeof(T1) < sizeof(T2) > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using max_type = boost::mp11::mp_max_element < D, Comparator > ;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T > constexpr auto index_v = boost::mp11::mp_find < D, T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert(size_v < Deque <     > > == 0 && empty_v < Deque <     > > == 1);

    static_assert(size_v < Deque < int > > == 1 && empty_v < Deque < int > > == 0);

//  -------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <      front < Deque < int >       > ,         int        > );

    static_assert(std::is_same_v < push_front < Deque < int > , int > , Deque < int, int > > );

    static_assert(std::is_same_v <  pop_front < Deque < int >       > , Deque <          > > );

//  -------------------------------------------------------------------------------------------

    static_assert(std::is_same_v <       back < Deque < int >       > ,              int   > );

    static_assert(std::is_same_v <  push_back < Deque < int > , int > , Deque < int, int > > );

    static_assert(std::is_same_v <   pop_back < Deque < int >       > , Deque <          > > );

//  -------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < at < Deque < int, int > , 0 > , int > );

    static_assert(std::is_same_v < at < Deque < int, int > , 1 > , int > );

//  -------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < max_type < Deque < int, double > > , double > );

//  -------------------------------------------------------------------------------------------

    static_assert(index_v < Deque < int > , int > == 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////