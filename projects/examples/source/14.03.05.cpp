///////////////////////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <barrier>
#include <cassert>
#include <chrono>
#include <future>
#include <new>

///////////////////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////////////////

struct alignas(std::hardware_constructive_interference_size) Entity_v1
{
    std::atomic < int > x = 0, y = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

struct Entity_v2
{
    alignas(std::hardware_destructive_interference_size) std::atomic < int > x = 0, y = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Task
{
public:

    Task(std::barrier <> & barrier, std::atomic < int > & x) : m_barrier(barrier), m_x(x) {}

//  -------------------------------------------------------------------------------------------

    auto operator()() const
    {
        m_barrier.arrive_and_wait();

        auto begin = std::chrono::steady_clock::now();

        for (auto i = 0uz; i < 1'000'000; ++i)
        {
            m_x.store(i + 1);
        }

        auto delta = std::chrono::steady_clock::now() - begin;

        return std::chrono::duration_cast < std::chrono::duration < double > > (delta).count();
    }

private:

    std::barrier <> & m_barrier;

    std::atomic < int > & m_x;
};

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v1(benchmark::State & state)
{
    std::barrier <> barrier(3);

	Entity_v1 entity;

    Task task_1(barrier, entity.x);

    Task task_2(barrier, entity.y);
	
    for (auto element : state)
    {
        auto future_1 = std::async(std::launch::async, task_1);

        auto future_2 = std::async(std::launch::async, task_2);

        barrier.arrive_and_wait();

        state.SetIterationTime((future_1.get() + future_2.get()) / 2);

		benchmark::DoNotOptimize(entity);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v2(benchmark::State & state)
{
    std::barrier <> barrier(3);

	Entity_v2 entity;

    Task task_1(barrier, entity.x);

    Task task_2(barrier, entity.y);
	
    for (auto element : state)
    {
        auto future_1 = std::async(std::launch::async, task_1);

        auto future_2 = std::async(std::launch::async, task_2);

        barrier.arrive_and_wait();

        state.SetIterationTime((future_1.get() + future_2.get()) / 2);

		benchmark::DoNotOptimize(entity);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test_v1);

BENCHMARK(test_v2);

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    assert(2 * sizeof(Entity_v1) == sizeof(Entity_v2));

//  ---------------------------------------------------

    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////////////////