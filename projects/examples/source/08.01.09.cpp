#include <bit>
#include <cassert>
#include <cstddef>

//////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::endian::native == std::endian::little);

//  ----------------------------------------------------------

    auto x = 0x01020304;

//  ----------------------------------------------------------

    auto p_x = std::bit_cast < std::byte * > (&x);

//  ----------------------------------------------------------

    assert(std::to_integer < int > (*(p_x + 0)) == 4);

    assert(std::to_integer < int > (*(p_x + 1)) == 3);

    assert(std::to_integer < int > (*(p_x + 2)) == 2);

    assert(std::to_integer < int > (*(p_x + 3)) == 1);
}