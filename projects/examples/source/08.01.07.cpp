#include <bit>
#include <bitset>
#include <cassert>

//////////////////////////////////////////////////////////////////////////

int main()
{
    assert((std::bitset < 8 > (0b01) & std::bitset < 8 > (0b10)) == 0b00);

    assert((std::bitset < 8 > (0b01) | std::bitset < 8 > (0b10)) == 0b11);

//  ----------------------------------------------------------------------

    assert( std::bitset < 8 > (255).to_string() == "11111111");

    assert( std::bitset < 8 > ("11111111").to_ullong() == 255);

//  ----------------------------------------------------------------------

    assert( std::bit_floor(3u) == 2 && std::bit_ceil(3u) == 4);
}