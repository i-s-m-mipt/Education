//////////////////////////////////////////////////////////////

// chapter : Storage

//////////////////////////////////////////////////////////////

// section : Sequential Containers

//////////////////////////////////////////////////////////////

// content : Sequential Containers
//
// content : Static Arrays
//
// content : Container std::array
//
// content : Contiguous Iterators
//
// content : Concept std::contiguous_iterator

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