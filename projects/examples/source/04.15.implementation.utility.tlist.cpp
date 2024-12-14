#include <cstddef>
#include <iostream>
#include <type_traits>

#include <boost/type_index.hpp>

//  ================================================================================================

template < typename ... Ts > struct List {};

//  ================================================================================================

template < typename     T  > struct Size {};

template < typename ... Ts > struct Size < List < Ts ... > >
{
     static constexpr auto value = sizeof...(Ts);
};

template < typename L > constexpr auto size_v = Size < L > ::value;

template < typename L > constexpr auto empty_v = size_v < L > == 0;

//  ================================================================================================

template <             typename     T  > struct Front {};

template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > { using type = T; };

template < typename L > using front = typename Front < L > ::type;

//  ================================================================================================

template < typename T, typename     U  > struct Push_Front {};

template < typename T, typename ... Ts > struct Push_Front < T, List < Ts ... > >
{
    using type = List < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

//  ================================================================================================

template <             typename     T  > struct Pop_Front {};

template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
{
    using type = List < Ts ... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

//  ================================================================================================

template <             typename     T  > struct Back {};

template < typename T                  > struct Back < List < T > > { using type = T; };

template < typename T, typename ... Ts > struct Back < List < T, Ts ... > > 
{ 
    using type = typename Back < List < Ts ... > > ::type; 
};

template < typename L > using back = typename Back < L > ::type;

//  ================================================================================================

template < typename T, typename L, bool C = empty_v < L > > struct Push_Back {};

template < typename T, typename L > struct Push_Back < T, L, false >
{
    using type = push_front < front < L > , typename Push_Back < T, pop_front < L > > ::type > ;
}; 

template < typename T, typename L > struct Push_Back < T, L, true >
{
    using type = push_front < T, L > ;
};

template < typename T, typename L > using push_back = typename Push_Back < T, L > ::type;

//  ================================================================================================

template <             typename     T  > struct Pop_Back {};

template < typename T                  > struct Pop_Back < List < T > > { using type = List <> ; };

template < typename T, typename ... Ts > struct Pop_Back < List < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < List < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

//  ================================================================================================

template < typename L, std::size_t I > class Nth : public Nth < pop_front < L > , I - 1 > {};

template < typename L > class Nth < L, 0 > : public Front < L > {};

template < typename L, std::size_t I > using nth = typename Nth < L, I > ::type;

//  ================================================================================================

template < typename L, bool C = empty_v < L > > class Max_Type {};

template < typename L > class Max_Type < L, true  > { public: using type = std::byte; };

template < typename L > class Max_Type < L, false >
{
private:

    using contender = front < L > ;

    using best = typename Max_Type < pop_front < L > > ::type;

public:

    using type = std::conditional_t < sizeof(contender) >= sizeof(best), contender, best > ;
};

template < typename L > using max_type = typename Max_Type < L > ::type;

//  ================================================================================================

int main()
{
    using list_0 = List <          > ; 
    using list_1 = List < int      > ;
    using list_2 = List < int, int > ;

    using list_3 = push_back < int, list_2 > ;

//  ------------------------------------------------------------------------------------------------

    static_assert(size_v < list_0 > == 0 &&  empty_v < list_0 > );
    static_assert(size_v < list_1 > == 1 && !empty_v < list_1 > );
    static_assert(size_v < list_2 > == 2 && !empty_v < list_2 > );
    static_assert(size_v < list_3 > == 3 && !empty_v < list_3 > );

//  ------------------------------------------------------------------------------------------------

//  using     front_t_0 =     front < list_0 > ; // error
//  using pop_front_t_0 = pop_front < list_0 > ; // error

//  using      back_t_0 =      back < list_0 > ; // error
//  using  pop_back_t_0 =  pop_back < list_0 > ; // error

//  ------------------------------------------------------------------------------------------------

    std::cout << boost::typeindex::type_id_with_cvr < list_0 > ().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr < list_1 > ().pretty_name() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr < list_2 > ().pretty_name() << std::endl;

//  ------------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < front < push_front < int, list_2 > > , int > );
    static_assert(std::is_same_v < front <  pop_front <      list_2 > > , int > );

    static_assert(std::is_same_v <  back <  push_back < int, list_2 > > , int > );
    static_assert(std::is_same_v <  back <   pop_back <      list_2 > > , int > );

//  ------------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < nth < list_3, 0 > , int > );
    static_assert(std::is_same_v < nth < list_3, 1 > , int > );
    static_assert(std::is_same_v < nth < list_3, 2 > , int > );
//  static_assert(std::is_same_v < nth < list_3, 3 > , int > ); // error

//  ------------------------------------------------------------------------------------------------

    static_assert(std::is_same_v < max_type < list_3 > , int > );
}