#include <cassert>
#include <iostream>
#include <typeinfo>
#include <type_traits>

#include <boost/type_index.hpp>

// =================================================================================================

template < typename ... Ts > struct list {};

template < typename     L  > struct size {};

template < typename ... Ts > struct size < list < Ts ... > >
{
     static constexpr std::size_t value = sizeof...(Ts);
};

template < typename L > inline constexpr std::size_t size_v = size < L > ::value;

template < typename L > inline constexpr bool empty_v = (size_v < L > == 0);

// =================================================================================================

template <             typename     L  > struct Front {}; // note: compile error for empty list

template < typename T, typename ... Ts > struct Front < list < T, Ts ... > > { using type = T; };

template < typename L > using front = typename Front < L > ::type;

// =================================================================================================

template < typename T, typename     L  > struct Push_Front {}; 

template < typename T, typename ... Ts > struct Push_Front < T, list < Ts ... > >
{
    using type = list < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

// =================================================================================================

template <             typename     L  > struct Pop_Front {}; // note: compile error for empty list

template < typename T, typename ... Ts > struct Pop_Front < list < T, Ts ... > >
{
    using type = list < Ts... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

// =================================================================================================

template <             typename     L  > struct Back {}; // note: compile error for empty list

template < typename T                  > struct Back < list < T > > { using type = T; };

template < typename T, typename ... Ts > struct Back < list < T, Ts ... > > 
{ 
    using type = typename Back < list < Ts ... > > ::type; 
};

template < typename L > using back = typename Back < L > ::type;

// =================================================================================================

template < typename T, typename L, bool E = empty_v < L > > struct Push_Back {};

template < typename T, typename L > struct Push_Back < T, L, false >
{
    using type = push_front < front < L >, typename Push_Back < T, pop_front < L > > ::type > ;
}; 

template < typename T, typename L > struct Push_Back < T, L, true >
{
    using type = push_front < T, L > ;
};

template < typename T, typename L > using push_back = typename Push_Back < T, L > ::type;

// =================================================================================================

template <             typename     L  > struct Pop_Back{}; // note: compile error for empty list

template < typename T                  > struct Pop_Back < list < T > > { using type = list <> ; };

template < typename T, typename ... Ts > struct Pop_Back < list < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < list < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

// =================================================================================================

template < typename L, auto N > struct Nth : Nth < pop_front < L > , N - 1 > {};

template < typename L > struct Nth < L, 0 > : Front < L > {};

template < typename L, auto N > using nth = typename Nth < L, N > ::type;

// =================================================================================================

int main()
{
    using list_0 = list <            > ; 
    using list_1 = list < bool       > ;
    using list_2 = list < bool, char > ;

    using list_3 = push_back < int, list_2 > ; // note: list < bool, char, int >

    static_assert( empty_v < list_0 > && size_v < list_0 > == 0);
    static_assert(!empty_v < list_1 > && size_v < list_1 > == 1);
    static_assert(!empty_v < list_2 > && size_v < list_2 > == 2);
    static_assert(!empty_v < list_3 > && size_v < list_3 > == 3);

//  using     front_t_0 =     front < list_0 > ; // error: empty list
//  using pop_front_t_0 = pop_front < list_0 > ; // error: empty list

//  using     back__t_0 =     back  < list_0 > ; // error: empty list
//  using pop_back__t_0 = pop_back  < list_0 > ; // error: empty list

    using boost::typeindex::type_id_with_cvr;

    std::cout << type_id_with_cvr <                   list_0      > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <                   list_1      > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <                   list_2      > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <      front <      list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr < push_front < int, list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <  pop_front <      list_2    > > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <      back  <      list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr < push_back  < int, list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <  pop_back  <      list_2    > > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <             nth < list_3, 0 > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <             nth < list_3, 1 > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <             nth < list_3, 2 > > ().pretty_name() << std::endl;

    return 0;
}