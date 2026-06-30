///////////////////////////////////////////////////////////////////////////////////////////

// chapter : Applied Computations

///////////////////////////////////////////////////////////////////////////////////////////

// content : Timing
//
// content : ReaD Time-Stamp Counter (RDTSC)
//
// content : Intrinsic __rdtscp
//
// content : Invariant TSC
//
// content : Function std::this_thread::sleep_for

///////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <print>
#include <thread>

///////////////////////////////////////////////////////////////////////////////////////////

#include <x86intrin.h>

///////////////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > > class Timer
{
public :

	Timer(char const * scope) : m_scope(scope)
    {
        std::call_once(s_flag, initialize);

        m_begin = __rdtscp(&m_data); // support : https://compiler-explorer.com
    }

//  ---------------------------------------------------------------------------------------

   ~Timer()
	{
		std::print("{} : {:.6f}\n", m_scope, elapsed().count());
	}

//  ---------------------------------------------------------------------------------------

	auto elapsed() const
	{
        return std::chrono::duration_cast < D >
        (
            std::chrono::nanoseconds
            (
                static_cast < std::int64_t >
                (
                    (__rdtscp(&m_data) - m_begin) / s_ticks_per_nanosecond
                )
            )
        );
	}

private :

    static void initialize()
    {
        std::uint32_t data = 0;

        auto now_1 = std::chrono::steady_clock::now();

        auto tsc_1 = __rdtscp(&data);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        auto tsc_2 = __rdtscp(&data);

        auto now_2 = std::chrono::steady_clock::now();

        s_ticks_per_nanosecond =
        (
            static_cast < double > (tsc_2 - tsc_1) /

            std::chrono::duration_cast < std::chrono::nanoseconds > (now_2 - now_1).count()
        );
    }

//  ---------------------------------------------------------------------------------------

	char const * m_scope = nullptr;

	std::uint64_t m_begin = 0;

//  ---------------------------------------------------------------------------------------

    mutable std::uint32_t m_data = 0;

//  ---------------------------------------------------------------------------------------

    static inline std::once_flag s_flag;

    static inline auto s_ticks_per_nanosecond = 0.0;
};

///////////////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(x), 2) + std::pow(std::cos(x), 2);
	}

	return x;
}

///////////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	Timer timer("main : timer");

//  -------------------------------------------

	assert(equal(calculate(1 << 20), 1 << 20));
}

///////////////////////////////////////////////////////////////////////////////////////////