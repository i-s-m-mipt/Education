#include <cassert>
#include <iostream>
#include <typeinfo>
#include <type_traits>

#include <boost/type_index.hpp>

// =================================================================================================

template < typename ... Ts > struct Type_List {};

template < typename     L  > struct Size {};

template < typename ... Ts > struct Size < Type_List < Ts ... > >
{
     static constexpr auto value = sizeof...(Ts);
};

template < typename L > inline constexpr auto  size_v = Size < L > ::value;

template < typename L > inline constexpr auto empty_v = (size_v < L > == 0);

// =================================================================================================

template <             typename     L  > struct Front {}; // note: compile error for empty Type_List

template < typename T, typename ... Ts > struct Front < Type_List < T, Ts ... > > { using type = T; };

template < typename L > using front = typename Front < L > ::type;

// =================================================================================================

template < typename T, typename     L  > struct Push_Front {}; 

template < typename T, typename ... Ts > struct Push_Front < T, Type_List < Ts ... > >
{
    using type = Type_List < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

// =================================================================================================

template <             typename     L  > struct Pop_Front {}; // note: compile error for empty Type_List

template < typename T, typename ... Ts > struct Pop_Front < Type_List < T, Ts ... > >
{
    using type = Type_List < Ts... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

// =================================================================================================

template <             typename     L  > struct Back {}; // note: compile error for empty Type_List

template < typename T                  > struct Back < Type_List < T > > { using type = T; };

template < typename T, typename ... Ts > struct Back < Type_List < T, Ts ... > > 
{ 
    using type = typename Back < Type_List < Ts ... > > ::type; 
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

template <             typename     L  > struct Pop_Back{}; // note: compile error for empty Type_List

template < typename T                  > struct Pop_Back < Type_List < T > > { using type = Type_List <> ; };

template < typename T, typename ... Ts > struct Pop_Back < Type_List < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < Type_List < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

// =================================================================================================

template < typename L, auto N > struct Nth : public Nth < pop_front < L > , N - 1 > {};

template < typename L > struct Nth < L, 0 > : public Front < L > {};

template < typename L, auto N > using nth = typename Nth < L, N > ::type;

// =================================================================================================

int main()
{
    using type_list_0 = Type_List <            > ; 
    using type_list_1 = Type_List < bool       > ;
    using type_list_2 = Type_List < bool, char > ;

    using type_list_3 = push_back < int, type_list_2 > ; // note: Type_List < bool, char, int >

    static_assert(size_v < type_list_0 > == 0 &&  empty_v < type_list_0 > );
    static_assert(size_v < type_list_1 > == 1 && !empty_v < type_list_1 > );
    static_assert(size_v < type_list_2 > == 2 && !empty_v < type_list_2 > );
    static_assert(size_v < type_list_3 > == 3 && !empty_v < type_list_3 > );

//  using     front_t_0 =     front < type_list_0 > ; // error: empty Type_List
//  using pop_front_t_0 = pop_front < type_list_0 > ; // error: empty Type_List

//  using      back_t_0 =      back < type_list_0 > ; // error: empty Type_List
//  using  pop_back_t_0 =  pop_back < type_list_0 > ; // error: empty Type_List

    using boost::typeindex::type_id_with_cvr; // note: better than plain typeid

    std::cout << type_id_with_cvr <                   type_list_0      > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <                   type_list_1      > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <                   type_list_2      > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <      front <      type_list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr < push_front < int, type_list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <  pop_front <      type_list_2    > > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <       back <      type_list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <  push_back < int, type_list_2    > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <   pop_back <      type_list_2    > > ().pretty_name() << std::endl;

    std::cout << type_id_with_cvr <        nth <      type_list_3, 0 > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <        nth <      type_list_3, 1 > > ().pretty_name() << std::endl;
    std::cout << type_id_with_cvr <        nth <      type_list_3, 2 > > ().pretty_name() << std::endl;

    return 0;
}