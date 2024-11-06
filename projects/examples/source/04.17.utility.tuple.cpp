#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>

using namespace std::literals;

//  ================================================================================================

template < typename T, std::size_t I > struct Helper
{
    static void print(std::ostream & stream, const T & tuple)
    {
        Helper < T, I - 1 > ::print(stream, tuple);

        stream << " " << std::get < I - 1 > (tuple);
    }
};
    
template < typename T > struct Helper < T, 1 >
{
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
    constexpr auto tuple_c = std::make_tuple('a', 1, 1.0);

//  ------------------------------------------------------

    using tuple_t = decltype(tuple_c);

    static_assert(std::tuple_size_v < tuple_t > == 3);

    static_assert(std::is_same_v < std::tuple_element_t < 1, tuple_t > , const int > );

    static_assert(std::get < 1 > (tuple_c) == std::get < int > (tuple_c));

//  ----------------------------------------------------------------------

    auto tuple_1 = std::make_tuple(1, "aaaaa"s);
    
    auto tuple_2 = tuple_1;
    
//  -----------------------------

	std::get < 0 > (tuple_2) = 2;

	std::get < 1 > (tuple_2) = "bbbbb"s;

//  ------------------------------------

    auto f = false, t = true;

//  ----------------------------------

    assert((tuple_1 <  tuple_2) == t);
    assert((tuple_1 >  tuple_2) == f);
    assert((tuple_1 <= tuple_2) == t);
    assert((tuple_1 >= tuple_2) == f);
    assert((tuple_1 == tuple_2) == f);
    assert((tuple_1 != tuple_2) == t);

//  ---------------------------------------------

    std::cout << "tuple_1 = " << tuple_1 << '\n';
	std::cout << "tuple_2 = " << tuple_2 << '\n';

//  ---------------------------------------------------------------

    auto x = 0; std::tie(x, std::ignore) = tuple_1; assert(x == 1);

    assert(std::tuple_cat(tuple_1, tuple_2) == std::make_tuple(1, "aaaaa"s, 2, "bbbbb"s));

    const auto & [data_1, data_2] = tuple_2; // support: cppinsights.io

    assert(data_1 == 2 && data_2 == "bbbbb");
}