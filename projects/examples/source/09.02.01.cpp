#include <cassert>
#include <iterator>
#include <vector>

///////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------

    auto iterator = vector.begin();

//  ---------------------------------------------------

    assert(std::distance(iterator, vector.end()) == 5);

//  ---------------------------------------------------

    std::advance(iterator, 2);

//  ---------------------------------------------------

    assert(*std::next(iterator, 1) == 4);

    assert(*std::prev(iterator, 1) == 2);
}