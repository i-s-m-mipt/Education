#include <cassert>
#include <iostream>
#include <typeinfo>
#include <type_traits>

#include <boost/type_index.hpp>

// =================================================================================================

template < typename ... Ts > struct Tlist {};

template < typename     L  > struct Size {};

template < typename ... Ts > struct Size < Tlist < Ts ... > >
{
     static constexpr auto value = sizeof...(Ts);
};

template < typename L > inline constexpr auto  size_v = Size < L > ::value;

template < typename L > inline constexpr auto empty_v = (size_v < L > == 0);

// =================================================================================================

template <             typename     L  > struct Front {}; // note: compile error for empty Tlist

template < typename T, typename ... Ts > struct Front < Tlist < T, Ts ... > > { using type = T; };

template < typename L > using front = typename Front < L > ::type;

// =================================================================================================

template < typename T, typename     L  > struct Push_Front {}; 

template < typename T, typename ... Ts > struct Push_Front < T, Tlist < Ts ... > >
{
    using type = Tlist < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

// =================================================================================================

template <             typename     L  > struct Pop_Front {}; // note: compile error for empty Tlist

template < typename T, typename ... Ts > struct Pop_Front < Tlist < T, Ts ... > >
{
    using type = Tlist < Ts ... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

// =================================================================================================

template <             typename     L  > struct Back {}; // note: compile error for empty Tlist

template < typename T                  > struct Back < Tlist < T > > { using type = T; };

template < typename T, typename ... Ts > struct Back < Tlist < T, Ts ... > > 
{ 
    using type = typename Back < Tlist < Ts ... > > ::type; 
};

template < typename L > using back = typename Back < L > ::type;

// =================================================================================================

template < typename T, typename L, bool E = empty_v < L > > struct Push_Back {};

template < typename T, typename L > struct Push_Back < T, L, false >
{
    using type = push_front < front < L > , typename Push_Back < T, pop_front < L > > ::type > ;
}; 

template < typename T, typename L > struct Push_Back < T, L, true >
{
    using type = push_front < T, L > ;
};

template < typename T, typename L > using push_back = typename Push_Back < T, L > ::type;

// =================================================================================================

template <             typename     L  > struct Pop_Back{}; // note: compile error for empty Tlist

template < typename T                  > struct Pop_Back < Tlist < T > > { using type = Tlist <> ; };

template < typename T, typename ... Ts > struct Pop_Back < Tlist < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < Tlist < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

// =================================================================================================

template < typename L, auto N > struct Nth : public Nth < pop_front < L > , N - 1 > {};

template < typename L > struct Nth < L, 0 > : public Front < L > {};

template < typename L, auto N > using nth = typename Nth < L, N > ::type;

// =================================================================================================

template < typename L, bool E = empty_v < L > > struct Max_Type {};

template < typename L > struct Max_Type < L, true  > { using type = char; };
template < typename L > struct Max_Type < L, false >
{
private:

    using contender = front < L > ;

    using best = typename Max_Type < pop_front < L > > ::type;

public:

    using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;

}; // template < typename L > class Max_Type < L, false >

template < typename L > using max_type = typename Max_Type < L > ::type;

// =================================================================================================

int main()
{
    using tlist_0 = Tlist <            > ; 
    using tlist_1 = Tlist < bool       > ;
    using tlist_2 = Tlist < bool, char > ;

    using tlist_3 = push_back < int, tlist_2 > ; // note: Tlist < bool, char, int >

    static_assert(size_v < tlist_0 > == 0 &&  empty_v < tlist_0 > );
    static_assert(size_v < tlist_1 > == 1 && !empty_v < tlist_1 > );
    static_assert(size_v < tlist_2 > == 2 && !empty_v < tlist_2 > );
    static_assert(size_v < tlist_3 > == 3 && !empty_v < tlist_3 > );

//  using     front_t_0 =     front < tlist_0 > ; // error: empty Tlist
//  using pop_front_t_0 = pop_front < tlist_0 > ; // error: empty Tlist

//  using      back_t_0 =      back < tlist_0 > ; // error: empty Tlist
//  using  pop_back_t_0 =  pop_back < tlist_0 > ; // error: empty Tlist

    using boost::typeindex::type_id_with_cvr; // note: better than plain typeid

    std::cout << type_id_with_cvr < tlist_0 > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr < tlist_1 > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr < tlist_2 > ().pretty_name() << std::endl;

    static_assert(std::is_same_v < front < push_front < int, tlist_2 > > , int  > );
    static_assert(std::is_same_v < front <  pop_front <      tlist_2 > > , char > );

    static_assert(std::is_same_v <  back <  push_back < int, tlist_2 > > , int  > );
    static_assert(std::is_same_v <  back <   pop_back <      tlist_2 > > , bool > );

    static_assert(std::is_same_v < nth < tlist_3, 0 > , bool > );
    static_assert(std::is_same_v < nth < tlist_3, 1 > , char > );
    static_assert(std::is_same_v < nth < tlist_3, 2 > , int  > );

    static_assert(std::is_same_v < max_type < tlist_3 > , int > );

    return 0;
}