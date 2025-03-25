#include <cstddef>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t S1, std::size_t S2 > struct Array 
{
    T array[S1][S2]{};
};

////////////////////////////////////////////////////////////////////////////

template < typename T, std::size_t S > using array_t = Array < T, S, S > ;

////////////////////////////////////////////////////////////////////////////

int main()
{
    array_t < int, 5 > array;

//  ------------------------------------------------------------------------

    static_assert(std::is_same_v < decltype(array), Array < int, 5, 5 > > );
}