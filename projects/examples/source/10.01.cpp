//////////////////////////////////////////////////////////////

#include <array>
#include <cassert>
#include <concepts>
#include <type_traits>

//////////////////////////////////////////////////////////////

int main()
{
    std::array < int, 5 > array = { 1, 2, 3, 4, 5 };
    
//  ----------------------------------------------------------

    static_assert
    (
        std::is_same_v 
        < 
            decltype(array)::iterator, int * 
        > 
    );

//  ----------------------------------------------------------

    static_assert
    (
        std::contiguous_iterator < decltype(array)::iterator >
    );

//  ----------------------------------------------------------

	assert(array.at(0) == 1);
}

//////////////////////////////////////////////////////////////