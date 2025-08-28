///////////////////////////////////////////////////////

#include <bit>
#include <cassert>
#include <cstddef>

///////////////////////////////////////////////////////

int main()
{
    assert(std::endian::native == std::endian::little);

//  ---------------------------------------------------

    auto x = 0x01020304;

//  ---------------------------------------------------

    auto byte = std::bit_cast < std::byte * > (&x);

//  ---------------------------------------------------

    assert(std::to_integer < int > (*(byte + 0)) == 4);

    assert(std::to_integer < int > (*(byte + 1)) == 3);

    assert(std::to_integer < int > (*(byte + 2)) == 2);

    assert(std::to_integer < int > (*(byte + 3)) == 1);
}

///////////////////////////////////////////////////////