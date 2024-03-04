#include <cassert>
#include <iostream>
#include <valarray>

int main() 
{
    std::valarray < int > vector = { 1, 2, 3, 4, 5 };

    assert(vector.min() == 1 && vector.max() == 5);

    vector[vector > 4] = 0; // note: vector contains 1 2 3 4 0

    std::valarray < std::size_t > indexes = { 1, 2, 3 };

    std::valarray < int > part; part.resize(std::size(indexes));

    part = vector[indexes]; // note: part contains 2 3 4

    auto shift = part.cshift(1); // note: shift contains 3 4 2
 
    assert(shift[0] == 3 && shift[1] == 4 && shift[2] == 2);
    
    std::valarray < int > vector_1 = { 1, 2, 3 };
    std::valarray < int > vector_2 = { 3, 2, 1 };

    assert((vector_1 * vector_2).sum() == 10); // note: scalar product

    std::valarray < int > matrix_1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::valarray < int > matrix_2 = { 1, 0, 0, 1, 0, 0, 1, 0, 0 }; 

    const std::size_t size = 3;

    std::valarray < int > slice_1 = matrix_1[std::slice(0, size, 1)];
    std::valarray < int > slice_2 = matrix_2[std::slice(0, size, 3)];

    assert((slice_1 * slice_2).sum() == 6);

    return 0;
}