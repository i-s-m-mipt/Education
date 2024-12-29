#include <cassert>
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t I = 0 > class Helper_v1
{
public:

    static void read(std::istream & stream, T & tuple)
    {
        stream >> std::get < I > (tuple);

        if constexpr (std::tuple_size_v < T > > I + 1)
        {
            Helper_v1 < T, I + 1 > ::read(stream, tuple);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto & operator>>(std::istream & stream, std::tuple < Ts ... > & tuple)
{
    Helper_v1 < std::tuple < Ts ... > > ::read(stream, tuple);

    return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t I = 0 > class Helper_v2
{
public:

    static void write(std::ostream & stream, const T & tuple)
    {
        stream << std::get < I > (tuple) << ' ';

        if constexpr (std::tuple_size_v < T > > I + 1)
        {
            Helper_v2 < T, I + 1 > ::write(stream, tuple);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template 
< 
    typename ... Ts 
> 
auto & operator<<(std::ostream & stream, const std::tuple < Ts ... > & tuple)
{
    stream << "{ "; 
    
    Helper_v2 < std::tuple < Ts ... > > ::write(stream, tuple);
    
    return stream << '}';
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::tuple < int, std::string > tuple_1(1, "aaaaa");

//  -----------------------------------------------------------------------------------

    assert(std::get < 0 > (tuple_1) == 1);

//  -----------------------------------------------------------------------------------

    std::cout << "main : enter std::tuple < int, std::string > : "; 
	
	std::tuple < int, std::string > tuple_2; std::cin >> tuple_2; 
	
	std::cout << "main : tuple_2 = " << tuple_2 << '\n';

//  -----------------------------------------------------------------------------------

    auto x1 = 0; std::tie(x1, std::ignore) = tuple_1; assert(x1 == 1);

    const auto & [x2, string] = tuple_1; // support: cppinsights.io

    assert(x2 == 1 && string == "aaaaa");

//  -----------------------------------------------------------------------------------

    assert(std::tuple_cat(tuple_1, std::tuple <> ()) == tuple_1);

//  -----------------------------------------------------------------------------------

    constexpr auto tuple_3 = std::make_tuple(1, 2, 3);

//  -----------------------------------------------------------------------------------

    static_assert(std::tuple_size_v < decltype(tuple_3) > == 3);

    static_assert(std::is_same_v < std::tuple_element_t < 0, decltype(tuple_3) > , const int > );

    static_assert(std::get < 0 > (tuple_3) == 1);
}