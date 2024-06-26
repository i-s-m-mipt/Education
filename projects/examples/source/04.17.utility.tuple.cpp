#include <iostream>
#include <ostream>
#include <tuple>
#include <type_traits>

//  ================================================================================================

namespace detail
{
    template < typename T, std::size_t N > struct Printer
    {
        static void print(std::ostream & stream, const T & tuple)
        {
            Printer < T, N - 1 > ::print(stream, tuple);

            stream << ", " << std::get < N - 1 > (tuple);
        }

    }; // template < typename T, std::size_t N > struct Printer
    
    template < typename T > struct Printer < T, 1 >
    {
        static void print(std::ostream & stream, const T & tuple)
        {
            stream << std::get < 0 > (tuple);
        }

    }; // template < typename T > struct Printer < T, 1 >

    template < typename ... Ts > requires (sizeof...(Ts) == 0)

    void print(std::ostream & stream, const std::tuple < Ts ... > & tuple)
    {
        stream << "{}";
    }
    
    template < typename ... Ts > requires (sizeof...(Ts) != 0)

    void print(std::ostream & stream, const std::tuple < Ts ... > & tuple)
    {
        stream << "{ ";

        Printer < decltype(tuple), sizeof...(Ts) > ::print(stream, tuple);

        stream << " }";
    }

} // namespace detail

//  ================================================================================================

template < typename ... Ts > 

inline std::ostream & operator<<(std::ostream & stream, const std::tuple < Ts ... > & tuple)
{
	detail::print(stream, tuple); return stream;
}

//  ================================================================================================

[[nodiscard]] inline constexpr int nodiscard_function() { return 42; }

//  ================================================================================================

int main()
{
    constexpr auto tuple_1 = std::make_tuple('a', 42, 3.14);

//  ================================================================================================

    using tuple_t = decltype(tuple_1);

    static_assert(std::tuple_size_v < tuple_t > == 3);

    static_assert(std::is_same_v < std::tuple_element_t < 0, tuple_t > , const char   > );
    static_assert(std::is_same_v < std::tuple_element_t < 1, tuple_t > , const int    > );
    static_assert(std::is_same_v < std::tuple_element_t < 2, tuple_t > , const double > );

//  ================================================================================================

    static_assert(std::get < 0 > (tuple_1) == std::get < char   > (tuple_1));
	static_assert(std::get < 1 > (tuple_1) == std::get < int    > (tuple_1));
	static_assert(std::get < 2 > (tuple_1) == std::get < double > (tuple_1));

//  ================================================================================================

    char c{}; [[maybe_unused]] int i{}; double d{};
 
    std::tie(c, std::ignore, d) = tuple_1;

    std::ignore = nodiscard_function();

    auto tuple_2 = std::make_tuple('b', 43, 3.15);

    std::cout << std::tuple_cat(tuple_1, tuple_2) << std::endl;
 
    auto & [rc, ri, rd] = tuple_2;

    rc = std::get < 0 > (tuple_1); 
    ri = std::get < 1 > (tuple_1);
    rd = std::get < 2 > (tuple_1);

//  ================================================================================================

    std::cout << tuple_2 << std::endl;

    return 0;
}