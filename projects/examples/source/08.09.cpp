///////////////////////////////////////////////////////

// chapter : Arithmetic

///////////////////////////////////////////////////////

// section : Bytes

///////////////////////////////////////////////////////

// content : Little and Big Endian Byte Orders
//
// content : Enumeration std::endian
//
// content : Function std::to_integer

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

    auto array = reinterpret_cast < std::byte * > (&x);

//  ---------------------------------------------------

    assert(std::to_integer < int > (array[0]) == 4);

    assert(std::to_integer < int > (array[1]) == 3);

    assert(std::to_integer < int > (array[2]) == 2);

    assert(std::to_integer < int > (array[3]) == 1);
}

///////////////////////////////////////////////////////