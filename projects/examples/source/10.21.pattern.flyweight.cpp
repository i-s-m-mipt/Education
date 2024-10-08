#include <cassert>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <boost/container_hash/hash.hpp>
#include <boost/flyweight.hpp>

//  ================================================================================================

struct Data { int array[1000]{}; };

//  ================================================================================================

struct Hash
{
    [[nodiscard]] std::size_t operator()(const Data & data) const noexcept
    {
        std::size_t seed = 0;

        for (const auto element : data.array) boost::hash_combine(seed, element);

        return seed;
    }

}; // struct Hash

//  ================================================================================================

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

//  ================================================================================================

class Storage 
{
public:

    using container = boost::flyweights::hashed_factory < Hash, Equal > ;

    struct X {};
    struct Y {};

    template < typename T > using tag = boost::flyweights::tag < T > ;

    explicit Storage(const Data & x, const Data & y) : m_x(x), m_y(y) {}

    boost::flyweight < Data, container, tag < X > > m_x;
    boost::flyweight < Data, container, tag < Y > > m_y;

}; // class Storage

//  ================================================================================================

int main() 
{
    constexpr std::size_t size = 100'000;

    std::vector < Storage > storages; storages.reserve(size);

    for (std::size_t i = 0; i < size; ++i) // detail: ~800(MB)
    {
        storages.emplace_back(Data { static_cast < int > (i) }, 
                              Data { static_cast < int > (i) });
    }

    std::cout << "Enter any character to continue: "; char c1{}; std::cin >> c1;

//  ================================================================================================

    storages.clear();

    for (std::size_t i = 0; i < size; ++i) // detail: ~400(MB)
    {
        storages.emplace_back(Data { static_cast < int > (i) }, Data{});
    }

    std::cout << "Enter any character to continue: "; char c2{}; std::cin >> c2;

//  ================================================================================================

    const Storage storage_1(Data { 1 }, Data{});
    const Storage storage_2(Data { 2 }, Data{});

    assert(&storage_1.m_x.get() != &storage_2.m_x.get());
    assert(&storage_1.m_y.get() == &storage_2.m_y.get());

    return 0;
}