#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>
#include <boost/flyweight.hpp>

// =================================================================================================

struct Data { int array[1000]{}; }; // note: some big data with many copies

// =================================================================================================

struct Hash
{
    [[nodiscard]] std::size_t operator()(const Data & data) const noexcept
    {
        std::size_t seed = 0;

        for (const auto element : data.array) boost::hash_combine(seed, element);

        return seed;
    }

}; // struct Hash

// =================================================================================================

struct Equal
{
    [[nodiscard]] bool operator()(const Data & lhs, const Data & rhs) const noexcept
    {
        for (std::size_t i = 0; i < std::size(lhs.array); ++i)
        {
            if (lhs.array[i] != rhs.array[i]) return false;
        }

        return true;
    }

}; // struct Equal

// =================================================================================================

class Storage 
{
public:

    using container = boost::flyweights::hashed_factory < Hash, Equal > ;

    struct X {};
    struct Y {};

    template < typename T > using tag = boost::flyweights::tag < T > ;

    explicit Storage(const Data & x, const Data & y) : m_x(x), m_y(y) {}

    boost::flyweight < Data, container, tag < X > > m_x; // compare with Data x;
    boost::flyweight < Data, container, tag < Y > > m_y; // compare with Data y;

}; // class Storage

// =================================================================================================

int main() 
{
    constexpr std::size_t size = 100'000;

    std::vector < Storage > storages; storages.reserve(size);

    for (std::size_t i = 0; i < size; ++i) // note: unique objects, double size, ~800(Mb)
    {
        storages.emplace_back(
            Data{ static_cast < int > (i) }, 
            Data{ static_cast < int > (i) });
    }

    std::cout << "Continue? (y/n) "; char c{}; std::cin >> c;

    storages.clear();

    for (std::size_t i = 0; i < size; ++i) // note: shared objects, single size, ~400(Mb)
    {
        storages.emplace_back(Data{ static_cast < int > (i) }, Data{});
    }

    std::cout << "Continue? (y/n) "; std::cin >> c;

    const Storage storage_1(Data{ 1 }, Data{});
    const Storage storage_2(Data{ 2 }, Data{});

    assert(&storage_1.m_x.get() != &storage_2.m_x.get());
    assert(&storage_1.m_y.get() == &storage_2.m_y.get());

    return 0;
}