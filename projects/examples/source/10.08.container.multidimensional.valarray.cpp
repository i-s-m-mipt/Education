#include <cassert>
#include <cstddef>
#include <iterator>
#include <valarray>

//////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{
    std::valarray < int > valarray_1 = { 1, 2, 3, 4, 5 };

    std::valarray < int > valarray_2(valarray_1.shift(1));

    std::valarray < int > valarray_3(valarray_1[valarray_1 < 4]);
    
    std::valarray < int > valarray_4(valarray_1[std::slice(0, 3, 1)]);
    
    std::valarray < int > valarray_5(valarray_1[std::valarray < std::size_t > ({ 0, 1, 2 })]);

    assert(std::size(valarray_1) == 5);

    assert(std::size(valarray_2) == 5 && valarray_2[0] == 2 && valarray_2[4] == 0);

    assert(std::size(valarray_3) == 3 && valarray_3.max() == 3);

    assert(std::size(valarray_4) == 3 && valarray_4.max() == 3);

    assert(std::size(valarray_5) == 3 && valarray_5.max() == 3);

    assert((valarray_3 * valarray_4).sum() == 14);
}