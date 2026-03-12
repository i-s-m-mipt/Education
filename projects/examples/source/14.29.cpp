///////////////////////////////////////////////////////////////////

#include <atomic>
#include <print>
#include <type_traits>
#include <vector>

///////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////

struct alignas(1 * 8) Entity_v1 { int x = 0; };

struct alignas(2 * 8) Entity_v2 { int x = 0; };

///////////////////////////////////////////////////////////////////

class Entity_v3
{
public :

    auto & operator=(Entity_v3 const &)
    {
        std::print("Entity_v3::operator=\n");

        return *this;
    }
};

///////////////////////////////////////////////////////////////////

class Entity_v4
{
public :

    virtual ~Entity_v4() = default;
};

///////////////////////////////////////////////////////////////////

class Entity_v5 {};

///////////////////////////////////////////////////////////////////

class Entity_v6 : public virtual Entity_v5 {};

///////////////////////////////////////////////////////////////////

void test(benchmark::State & state) 
{
    auto argument = state.range(0);

    auto size = 1'000uz;

    std::vector <               Entity_v1   > entities_v1_1(size);

    std::vector < std::atomic < Entity_v1 > > entities_v1_2(size);

    std::vector <               Entity_v2   > entities_v2_1(size);

    std::vector < std::atomic < Entity_v2 > > entities_v2_2(size);

    Entity_v1 entity_v1(1);

    Entity_v2 entity_v2(1);

    for (auto element : state)
    {
        for (auto i = 0uz; i < size; ++i)
        {
            switch (argument)
            {
                case 1 : { entities_v1_1[i] = entity_v1; break; }

                case 2 : { entities_v1_2[i] = entity_v1; break; }

                case 3 : { entities_v2_1[i] = entity_v2; break; }

                case 4 : { entities_v2_2[i] = entity_v2; break; }
            }
        }

        benchmark::DoNotOptimize(entities_v1_1);

        benchmark::DoNotOptimize(entities_v1_2);

        benchmark::DoNotOptimize(entities_v2_1);

        benchmark::DoNotOptimize(entities_v2_2);
    }
}

///////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

///////////////////////////////////////////////////////////////////

int main()
{
    static_assert(std::is_trivially_copyable_v < Entity_v1 > == 1);

    static_assert(std::is_trivially_copyable_v < Entity_v2 > == 1);

//  ---------------------------------------------------------------

    static_assert(std::is_trivially_copyable_v < Entity_v3 > == 0);

    static_assert(std::is_trivially_copyable_v < Entity_v4 > == 0);

    static_assert(std::is_trivially_copyable_v < Entity_v6 > == 0);

//  ---------------------------------------------------------------

    static_assert(sizeof(Entity_v1) == 1 * 8);

    static_assert(sizeof(Entity_v2) == 2 * 8);

//  ---------------------------------------------------------------

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)

    static_assert(std::atomic < Entity_v1 > ::is_always_lock_free);
    
#endif

//  ---------------------------------------------------------------

#if defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)

    static_assert(std::atomic < Entity_v2 > ::is_always_lock_free);
    
#endif

//  ---------------------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////