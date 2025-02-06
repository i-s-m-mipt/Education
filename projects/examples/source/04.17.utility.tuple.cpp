#include <cassert>
#include <cstddef>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>

using namespace std::literals;

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t I = 0 > class Handler_v1
{
public:

    static void read(std::istream & stream, T & tuple)
    {
        stream >> std::get < I > (tuple);

        if constexpr (std::tuple_size_v < T > > I + 1)
        {
            Handler_v1 < T, I + 1 > ::read(stream, tuple);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > auto & operator>>(std::istream & stream, std::tuple < Ts ... > & tuple)
{
    Handler_v1 < std::tuple < Ts ... > > ::read(stream, tuple);

    return stream;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t I = 0 > class Handler_v2
{
public:

    static void write(std::ostream & stream, const T & tuple)
    {
        stream << std::get < I > (tuple) << ' ';

        if constexpr (std::tuple_size_v < T > > I + 1)
        {
            Handler_v2 < T, I + 1 > ::write(stream, tuple);
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
    
    Handler_v2 < std::tuple < Ts ... > > ::write(stream, tuple);
    
    return stream << '}';
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        static_assert(std::get < 0 > (std::make_tuple(1, 2, 3)) == 1);
    }

//  ---------------------------------------------------------------------------------

    {
        std::cout << "main : enter std::tuple < int, std::string > : ";
	
	    std::tuple < int, std::string > tuple; std::cin >> tuple; 
	
	    std::cout << "main : tuple = " << tuple << '\n';
    }

//  ---------------------------------------------------------------------------------

    {
        auto tuple = std::make_tuple(1, "aaaaa"s);

        auto x = 0;
        
        std::tie(x, std::ignore) = tuple;
        
        assert(x == 1);

        const auto & [y, string] = tuple; // support: cppinsights.io

        assert(y == 1 && string == "aaaaa");

        assert(std::tuple_cat(tuple, std::tuple <> ()) == tuple);
    }

//  ---------------------------------------------------------------------------------

    {
        using tuple_t = std::tuple < int, std::string > ;

        static_assert(std::tuple_size_v < tuple_t > == 2);

        static_assert(std::is_same_v < std::tuple_element_t < 0, tuple_t > , int > );
    }
}