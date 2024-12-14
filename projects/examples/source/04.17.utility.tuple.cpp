#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>

//  ================================================================================================

template < typename T, std::size_t I > class Helper
{
public:

    static void print(std::ostream & stream, const T & tuple)
    {
        Helper < T, I - 1 > ::print(stream, tuple);

        stream << " " << std::get < I - 1 > (tuple);
    }
};
    
template < typename T > class Helper < T, 1 >
{
public:

    static void print(std::ostream & stream, const T & tuple)
    {
        stream << std::get < 0 > (tuple);
    }
};

//  ================================================================================================

template 
< 
    typename ... Ts 
> 
auto & operator<<(std::ostream & stream, const std::tuple < Ts ... > & tuple)
{
    if constexpr (sizeof...(Ts) > 0)
    {
        stream << "{ ";

        Helper < decltype(tuple), sizeof...(Ts) > ::print(stream, tuple);

        stream << " }";
    }
	else
    {
        stream << "{}";
    }
    
    return stream;
}

//  ================================================================================================

int main()
{
    std::tuple < int, std::string > tuple_1(1, "aaaaa");

//  ----------------------------------------------------

    assert(std::get < 0 > (tuple_1) == 1);

//  ---------------------------------------------

    std::cout << "tuple_1 = " << tuple_1 << '\n';

//  ------------------------------------------------------------------

    auto x1 = 0; std::tie(x1, std::ignore) = tuple_1; assert(x1 == 1);

    const auto & [x2, string] = tuple_1; // support: cppinsights.io

    assert(x2 == 1 && string == "aaaaa");

//  -------------------------------------------------------------

    assert(std::tuple_cat(tuple_1, std::tuple <> ()) == tuple_1);

//  -------------------------------------------------------------

    constexpr auto tuple_2 = std::make_tuple(1, 2, 3);

//  --------------------------------------------------

    using tuple_t = decltype(tuple_2);

//  --------------------------------------------------

    static_assert(std::tuple_size_v < tuple_t > == 3);

    static_assert(std::is_same_v < std::tuple_element_t < 0, tuple_t > , const int > );

    static_assert(std::get < 0 > (tuple_2) == 1);
}