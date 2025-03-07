#include <cassert>
#include <cstddef>

///////////////////////////////////////////////////////////////////

int main()
{
    assert((std::byte(0b01) & std::byte(0b10)) == std::byte(0b00));

    assert((std::byte(0b01) | std::byte(0b10)) == std::byte(0b11));
}