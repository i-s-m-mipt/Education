#include <bitset>
#include <cassert>

//////////////////////////////////////////////////////////////////////////

int main()
{
    assert((std::bitset < 8 > (0b01) & std::bitset < 8 > (0b10)) == 0b00);

    assert((std::bitset < 8 > (0b01) | std::bitset < 8 > (0b10)) == 0b11);

//  ----------------------------------------------------------------------

    assert((std::bitset < 8 > (255).to_string()) == "11111111");

    assert((std::bitset < 8 > ("11111111").to_ullong()) == 255);
}