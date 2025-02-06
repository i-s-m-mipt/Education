#include <cstddef>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct List {};

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L > struct Size {};

template < typename ... Ts > struct Size < List < Ts ... > >
{
     static constexpr auto value = sizeof...(Ts);
};

template < typename L > constexpr auto size_v = Size < L > ::value;

template < typename L > constexpr auto empty_v = size_v < L > == 0;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L > struct Front {};

template < typename T, typename ... Ts > struct Front < List < T, Ts ... > > 
{ 
    using type = T;
};

template < typename L > using front = typename Front < L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename L > struct Push_Front {};

template < typename T, typename ... Ts > struct Push_Front < T, List < Ts ... > >
{
    using type = List < T, Ts ... > ;
};

template < typename T, typename L > using push_front = typename Push_Front < T, L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L > struct Pop_Front {};

template < typename T, typename ... Ts > struct Pop_Front < List < T, Ts ... > >
{
    using type = List < Ts ... > ;
};

template < typename L > using pop_front = typename Pop_Front < L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L > struct Back {};

template < typename T > struct Back < List < T > > 
{ 
    using type = T;
};

template < typename T, typename ... Ts > struct Back < List < T, Ts ... > > 
{ 
    using type = typename Back < List < Ts ... > > ::type;
};

template < typename L > using back = typename Back < L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename L, bool C = empty_v < L > > struct Push_Back {};

template < typename T, typename L > struct Push_Back < T, L, 0 >
{
    using type = push_front < front < L > , typename Push_Back < T, pop_front < L > > ::type > ;
};

template < typename T, typename L > struct Push_Back < T, L, 1 >
{
    using type = push_front < T, L > ;
};

template < typename T, typename L > using push_back = typename Push_Back < T, L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L > struct Pop_Back {};

template < typename T > struct Pop_Back < List < T > > 
{ 
    using type = List <> ;
};

template < typename T, typename ... Ts > struct Pop_Back < List < T, Ts ... > >
{
    using type = push_front < T, typename Pop_Back < List < Ts ... > > ::type > ;
};

template < typename L > using pop_back = typename Pop_Back < L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L, std::size_t I > class Nth : public Nth < pop_front < L > , I - 1 > {};

template < typename L > class Nth < L, 0 > : public Front < L > {};

template < typename L, std::size_t I > using nth = typename Nth < L, I > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

template < typename L, bool C = empty_v < L > > class Max_Type {};

template < typename L > class Max_Type < L, 1 > { public: using type = std::byte; };

template < typename L > class Max_Type < L, 0 >
{
private:

    using contender = front < L > ;

    using best = typename Max_Type < pop_front < L > > ::type;

public:

    using type = std::conditional_t < sizeof(contender) >= sizeof(best), contender, best > ;
};

template < typename L > using max_type = typename Max_Type < L > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        static_assert(size_v < List < int > > == 1 && !empty_v < List < int > > );
    }

//  --------------------------------------------------------------------------------------------

    {
        static_assert(std::is_same_v <      front <      List < int > > , int > );

        static_assert(std::is_same_v < push_front < int, List < int > > , List < int, int > > );

        static_assert(std::is_same_v <  pop_front <      List < int > > , List <> > );
    }

//  --------------------------------------------------------------------------------------------

    {
        static_assert(std::is_same_v <       back <      List < int > > , int > );

        static_assert(std::is_same_v <  push_back < int, List < int > > , List < int, int > > );

        static_assert(std::is_same_v <   pop_back <      List < int > > , List <> > );
    }

//  --------------------------------------------------------------------------------------------

    {
        static_assert(std::is_same_v < nth < List < int, int >, 0 > , int > );

        static_assert(std::is_same_v < nth < List < int, int >, 1 > , int > );
    }

//  --------------------------------------------------------------------------------------------

    {
        static_assert(std::is_same_v < max_type < List < int, double > > , double > );
    }
}