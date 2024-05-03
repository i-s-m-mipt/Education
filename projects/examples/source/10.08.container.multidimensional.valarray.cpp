#include <cassert>
#include <iterator>
#include <valarray>

int main() 
{
    std::valarray < int > valarray { 1, 2, 3, 4, 5 };

    assert(valarray.min() == 1 && valarray.max() == 5);

    valarray[valarray > 4] = 0; // note: elements: { 1, 2, 3, 4, 0 }

    const std::valarray < std::size_t > indexes { 1, 2, 3 };

    std::valarray < int > part; part.resize(std::size(indexes));

    part = valarray[indexes]; // note: elements: { 2, 3, 4 }

    const auto shift = part.cshift(1); // note: elements: { 3, 4, 2 }
 
    assert(shift[0] == 3 && shift[1] == 4 && shift[2] == 2);

//  ================================================================================================
    
    const std::valarray < int > valarray_1 { 1, 2, 3 };
    const std::valarray < int > valarray_2 { 3, 2, 1 };

    assert((valarray_1 * valarray_2).sum() == 10); // note: scalar product

//  ================================================================================================

    const std::valarray < int > valarray_3 { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const std::valarray < int > valarray_4 { 1, 0, 0, 1, 0, 0, 1, 0, 0 }; 

    constexpr std::size_t size = 3;

    std::valarray < int > slice_1 = valarray_3[std::slice(0, size, 1)];
    std::valarray < int > slice_2 = valarray_4[std::slice(0, size, 3)];

    assert((slice_1 * slice_2).sum() == 6);

    return 0;
}