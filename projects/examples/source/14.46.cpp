///////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

///////////////////////////////////////////////////////////////////////////////////

// content : Spinlocks
//
// content : Read-Modify-Write (RMW) Instructions
//
// content : Cache Thrashing
//
// content : Cache Coherency Traffic
//
// content : Reducing Load-Store Unit Utilization
//
// content : Intrinsic _mm_pause
//
// content : Microbenchmarking

///////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <atomic>
#include <barrier>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <ranges>
#include <thread>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////

#include <x86intrin.h>

///////////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>

///////////////////////////////////////////////////////////////////////////////////

#include "08.36.hpp"

///////////////////////////////////////////////////////////////////////////////////

class Spinlock_v1
{
public :

    void lock()
    {
        while (m_flag.exchange(true));
    }

//  ------------------------------------

    void unlock()
    {
        m_flag.store(false);
    }

private :

    std::atomic < bool > m_flag = false;
};

///////////////////////////////////////////////////////////////////////////////////

class Spinlock_v2
{
public :

    void lock()
    {
        while (m_flag.exchange(true, std::memory_order::acquire));
    }

//  --------------------------------------------------------------

    void unlock()
    {
        m_flag.store(false, std::memory_order::release);
    }

private :

    std::atomic < bool > m_flag = false;
};

///////////////////////////////////////////////////////////////////////////////////

class Spinlock_v3
{
public :

    void lock()
    {
        while (true)
        {
            if (!m_flag.exchange(true, std::memory_order::acquire))
            {
                break;
            }

            while (m_flag.load(std::memory_order::relaxed));
        }
    }

//  ---------------------------------------------------------------

    void unlock()
    {
        m_flag.store(false, std::memory_order::release);
    }

private :

    std::atomic < bool > m_flag = false;
};

///////////////////////////////////////////////////////////////////////////////////

class Spinlock_v4
{
public :

    void lock() // support : https://compiler-explorer.com
    {
        while (true)
        {
            if (!m_flag.exchange(true, std::memory_order::acquire))
            {
                break;
            }

            while (m_flag.load(std::memory_order::relaxed))
            {
                _mm_pause();
            }
        }
    }

//  ---------------------------------------------------------------

    void unlock()
    {
        m_flag.store(false, std::memory_order::release);
    }

private :

    std::atomic < bool > m_flag = false;
};

///////////////////////////////////////////////////////////////////////////////////

class Task_Base
{
public :

    virtual ~Task_Base() = default;

//  ------------------------------------------

    auto operator()(std::barrier <> & barrier)
    {
        barrier.arrive_and_wait();

        Timer timer;

        test();

        return timer.elapsed().count();
    }

//  ------------------------------------------

    virtual void test() = 0;
};

///////////////////////////////////////////////////////////////////////////////////

template < typename S > class Task : public Task_Base
{
public :

    void test() override
    {
        for (auto i = 0uz; i < 1 << 10; ++i)
        {
            std::scoped_lock < S > lock(m_spinlock);

            ++m_x;
        }
    }

private :

    int m_x = 0;

//  ------------------------------------------------

    mutable S m_spinlock;
};

///////////////////////////////////////////////////////////////////////////////////

void test(benchmark::State & state)
{
    auto argument = state.range(0);

    auto concurrency = std::thread::hardware_concurrency();

    std::vector < std::future < double > > futures(concurrency);

    std::shared_ptr < Task_Base > task;

    switch (argument)
    {
        case 1 : { task = std::make_shared < Task < Spinlock_v1 > > (); break; }

        case 2 : { task = std::make_shared < Task < Spinlock_v2 > > (); break; }

        case 3 : { task = std::make_shared < Task < Spinlock_v3 > > (); break; }

        case 4 : { task = std::make_shared < Task < Spinlock_v4 > > (); break; }
    }

    std::barrier <> barrier(concurrency + 1);

    auto lambda = [](auto & future) static { return future.get(); };

    for (auto element : state)
    {
        for (auto & future : futures)
        {
            future = std::async
            (
                std::launch::async, &Task_Base::operator(), task, std::ref(barrier)
            );
        }

        barrier.arrive_and_wait();

        auto time = *std::ranges::fold_left_first
        (
            std::views::transform(futures, lambda), std::plus()
        );

        state.SetIterationTime(time / concurrency);

		benchmark::DoNotOptimize(*task);
    }
}

///////////////////////////////////////////////////////////////////////////////////

BENCHMARK(test)->Arg(1)->Arg(2)->Arg(3)->Arg(4);

///////////////////////////////////////////////////////////////////////////////////

int main()
{
    benchmark::RunSpecifiedBenchmarks();
}

///////////////////////////////////////////////////////////////////////////////////