#include <cassert>
#include <concepts>
#include <string>
#include <type_traits>
#include <vector>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > concept integral = std::is_integral_v < T > ;

template < typename T > concept floating_point = std::is_floating_point_v < T > ;

template < typename T > concept arithmetic = integral < T > || floating_point < T > ;

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > concept addable = requires (T x, T y) { x + y; };

template < typename T > concept equable = requires (T x, T y)
{
    { x == y } -> std::convertible_to < bool > ;

    { x != y } -> std::convertible_to < bool > ;
};

template < typename T > concept ordable = equable < T > && requires (T x, T y)
{
    { x <  y } -> std::convertible_to < bool > ;
    
    { x <= y } -> std::convertible_to < bool > ;

    { x >  y } -> std::convertible_to < bool > ;

    { x >= y } -> std::convertible_to < bool > ;
};

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > concept typable = requires 
{ 
    typename T::value_type; 
};

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > auto max_v1(T x, T y) requires integral < T >
{
	return x < y ? y : x;
}

auto max_v2(integral auto x, integral auto y)
{
	return x < y ? y : x;
}

template < integral T > auto max_v3(T x, T y)
{
	return x < y ? y : x;
}

/////////////////////////////////////////////////////////////////////////////////////

template < typename T > requires std::regular < T > struct Entity {};

/////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        static_assert( integral       < int > && !integral       < double > );

        static_assert(!floating_point < int > &&  floating_point < double > );

        static_assert( arithmetic     < int > &&  arithmetic     < double > );
    }
    
//  --------------------------------------------------------------------------

    {
        static_assert(addable < int > && !addable < Entity < int > > );    

        static_assert(equable < int > && !equable < Entity < int > > );

        static_assert(ordable < int > && !ordable < Entity < int > > );
    }

//  --------------------------------------------------------------------------

    {
        static_assert(typable < std::vector < int > > );
    }

//  --------------------------------------------------------------------------

    {
        assert(max_v1(1, 2) == 2);

        assert(max_v2(1, 2) == 2);

        assert(max_v3(1, 2) == 2);
    }

//  --------------------------------------------------------------------------

    {
//      assert(equal(max_v1(1.0, 2.0), 2.0)); // error

//      assert(equal(max_v2(1.0, 2.0), 2.0)); // error

//      assert(equal(max_v3(1.0, 2.0), 2.0)); // error
    }

//  --------------------------------------------------------------------------
 
    {
        [[maybe_unused]] Entity < int   > entity_1;

//      [[maybe_unused]] Entity < int & > entity_2; // error
    }
}