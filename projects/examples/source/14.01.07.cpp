////////////////////////////////////////////////////////////

#include <cassert>
#include <thread>

////////////////////////////////////////////////////////////

             auto g_x = 1;

thread_local auto g_y = 2;

////////////////////////////////////////////////////////////

void test_v1() { ++g_x; } // support : compiler-explorer.com

void test_v2() { ++g_y; } // support : compiler-explorer.com

////////////////////////////////////////////////////////////

int main()
{
    std::jthread { test_v1 }; assert(g_x == 2);

    std::jthread { test_v2 }; assert(g_y == 2);
}

////////////////////////////////////////////////////////////