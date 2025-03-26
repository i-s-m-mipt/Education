#include <algorithm>
#include <cassert>
#include <vector>

/////////////////////////////////////////////////////////////////////////

// support : www.cs.usfca.edu/~galles/visualization/Heap.html

/////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------------------

    std::ranges::make_heap(vector);

//  ---------------------------------------------------------------------

    assert(vector == std::vector < int > ({ 5, 4, 3, 1, 2 }));

//  ---------------------------------------------------------------------

    auto size = std::size(vector);

//  ---------------------------------------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        if (2 * i + 1 < size) { assert(vector[i] >= vector[2 * i + 1]); }

        if (2 * i + 2 < size) { assert(vector[i] >= vector[2 * i + 2]); }
    }

//  ---------------------------------------------------------------------

    assert(std::ranges::max_element(vector) == std::begin(vector));
}