////////////////////////////////////////////////////////////////////

#include <bit>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <type_traits>

////////////////////////////////////////////////////////////////////

template < typename T2, typename T1 > T2 bit_cast(T1 const & source)
{
    static_assert(std::is_trivially_constructible_v < T2 > );

    static_assert(sizeof(T1) == sizeof(T2));

    static_assert(std::is_trivially_copyable_v < T1 > );

    static_assert(std::is_trivially_copyable_v < T2 > );
 
    T2 destination;

    std::memcpy(&destination, &source, sizeof(T2));

    return destination;
}

////////////////////////////////////////////////////////////////////

int main()
{
    auto x = 1.0;

//  -------------------------------------------------

    [[maybe_unused]] std::uint64_t y = 0, z = 0;

//  -------------------------------------------------

    *reinterpret_cast < char   * > (&y) = 0;

//  *reinterpret_cast < double * > (&y) = x; // error

//  -------------------------------------------------

    y =      bit_cast < std::uint64_t > (x);

    z = std::bit_cast < std::uint64_t > (x);

//  -------------------------------------------------

    assert(y == z);
}

////////////////////////////////////////////////////////////////////