#include <cstddef>
#include <type_traits>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T                > class is_array          : public std::false_type {};

template < typename T                > class is_array < T[ ] > : public std:: true_type {};

template < typename T, std::size_t S > class is_array < T[S] > : public std:: true_type {};

///////////////////////////////////////////////////////////////////////////////////////////

template < typename T > constexpr auto is_array_v = is_array < T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    static_assert( is_array_v < int[5] > );

	static_assert( is_array_v < int[ ] > );

	static_assert(!is_array_v < int    > );
}