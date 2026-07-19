////////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallel Programming

////////////////////////////////////////////////////////////////////////////////////////

// content : Hardware Threads
//
// content : Function std::thread::hardware_concurrency
//
// content : Thread Affinities
//
// content : Standard Portable Operating System Interface (POSIX)
//
// content : Native Thread Handlers
//
// content : Preemptive and Cooperative Multitasking

////////////////////////////////////////////////////////////////////////////////////////

#include <bitset>
#include <cstring>
#include <print>
#include <thread>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

#include <pthread.h>

////////////////////////////////////////////////////////////////////////////////////////

void test(int x)
{
    std::print("test : x = {}\n", x);
}

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < std::jthread > threads;

//  ------------------------------------------------------------------------------------

    std::bitset < CPU_SETSIZE > bitset(0b0000'0000'0000'0001);

//  ------------------------------------------------------------------------------------

    cpu_set_t set;

//  ------------------------------------------------------------------------------------

    std::memcpy(&set, &bitset, sizeof(cpu_set_t));

//  ------------------------------------------------------------------------------------

    for (auto i = 1uz; i < std::thread::hardware_concurrency() + 1; ++i)
    {
        threads.emplace_back(test, i);

    //  --------------------------------------------------------------------------------

        pthread_setaffinity_np(threads.back().native_handle(), sizeof(cpu_set_t), &set);
    }
}

////////////////////////////////////////////////////////////////////////////////////////