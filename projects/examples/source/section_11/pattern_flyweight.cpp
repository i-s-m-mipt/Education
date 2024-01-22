#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>
#include <boost/flyweight.hpp>

struct Data
{
    int array[1000]{}; // note: some big data with many copies

}; // struct Data

struct Hash
{
    [[nodiscard]] auto operator()(const Data & data) const noexcept
    {
        std::size_t seed = 0;

        for (std::size_t i = 0; i < std::size(data.array); ++i)
        {
            boost::hash_combine(seed, data.array[i]);
        }

        return seed;
    }

}; // struct Hash

struct Equal
{
    [[nodiscard]] auto operator()(const Data & lhs, const Data & rhs) const noexcept
    {
        for (std::size_t i = 0; i < std::size(lhs.array); ++i)
        {
            if (lhs.array[i] != rhs.array[i]) return false;
        }

        return true;
    }

}; // struct Equal

struct Storage 
{
    explicit Storage(const Data & x, const Data & y) : m_x(x), m_y(y) {}

    using container = boost::flyweights::hashed_factory < Hash, Equal > ;

    struct X {};
    struct Y {};

    template < typename T > using tag = boost::flyweights::tag < T > ;

    boost::flyweight < Data, container, tag < X > > m_x; // Data m_x;
    boost::flyweight < Data, container, tag < Y > > m_y; // Data m_y;

}; // class Storage

int main() 
{
    const std::size_t size = 100'000;

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

    Storage storage_1(Data{ 1 }, Data{});
    Storage storage_2(Data{ 2 }, Data{});

    assert(&storage_1.m_x.get() != &storage_2.m_x.get());
    assert(&storage_1.m_y.get() == &storage_2.m_y.get());

    return 0;
}