//////////////////////////////////////////////////////////////////////////////////

// chapter : Applied Computations

//////////////////////////////////////////////////////////////////////////////////

// content : Reinterpreting Bits
//
// content : Operator reinterpret_cast
//
// content : Type Punning
//
// content : Strict Aliasing Rule
//
// content : Type Alias std::uint64_t
//
// content : Function std::memcpy
//
// content : Function std::bit_cast
//
// content : Function std::start_lifetime_as

//////////////////////////////////////////////////////////////////////////////////

#include <bit>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>

//////////////////////////////////////////////////////////////////////////////////

template < typename T2, typename T1 > T2 bit_cast(T1 const & source)
{
    static_assert(sizeof(T1) == sizeof(T2));

    T2 destination;

    std::memcpy(&destination, &source, sizeof(T2));

    return destination;
}

//////////////////////////////////////////////////////////////////////////////////

struct Entity
{
	int x = 0;
};

//////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1.0;

//  ------------------------------------------------------------------------------

    [[maybe_unused]] std::uint64_t y = 0, z = 0;

//  ------------------------------------------------------------------------------

    *reinterpret_cast < std::byte * > (&y) = std::byte(0x00);

//  *reinterpret_cast < double    * > (&y) = x; // error

//  ------------------------------------------------------------------------------

    y =      bit_cast < std::uint64_t > (x);

    z = std::bit_cast < std::uint64_t > (x);

//  ------------------------------------------------------------------------------

    assert(y == z);

//  ------------------------------------------------------------------------------

    std::byte array[sizeof(Entity)]
    {
        std::byte(0x01), std::byte(0x02), std::byte(0x03), std::byte(0x04)
    };

//  ------------------------------------------------------------------------------

//  assert(reinterpret_cast       < Entity * > (array)->x == 0x04030201); // error

    assert(std::start_lifetime_as < Entity   > (array)->x == 0x04030201);
}

//////////////////////////////////////////////////////////////////////////////////