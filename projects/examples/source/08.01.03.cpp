#include <cassert>

///////////////////////////////////////////////////////////////////

auto encode(unsigned int x)
{
    return x ^ x >> 1;
}

///////////////////////////////////////////////////////////////////

auto decode(unsigned int x)
{
    for (auto i = 1u << 31; i > 1; i >>= 1)
    {
        x = x & i ? x ^ i >> 1 : x;
    }

    return x;
}

///////////////////////////////////////////////////////////////////

int main()
{
    assert(0 == 0b000 && encode(0) == 0b000 && decode(0b000) == 0);
    
    assert(1 == 0b001 && encode(1) == 0b001 && decode(0b001) == 1);

    assert(2 == 0b010 && encode(2) == 0b011 && decode(0b011) == 2);

    assert(3 == 0b011 && encode(3) == 0b010 && decode(0b010) == 3);

    assert(4 == 0b100 && encode(4) == 0b110 && decode(0b110) == 4);

    assert(5 == 0b101 && encode(5) == 0b111 && decode(0b111) == 5);

    assert(6 == 0b110 && encode(6) == 0b101 && decode(0b101) == 6);

    assert(7 == 0b111 && encode(7) == 0b100 && decode(0b100) == 7);
}