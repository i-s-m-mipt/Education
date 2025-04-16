/////////////////////////////////////////////////////////////

#include <cassert>
#include <thread>

/////////////////////////////////////////////////////////////

             auto g_x1 = 1;

thread_local auto g_x2 = 2;

/////////////////////////////////////////////////////////////

void test_v1() { ++g_x1; } // support : compiler-explorer.com

void test_v2() { ++g_x2; } // support : compiler-explorer.com

/////////////////////////////////////////////////////////////

int main()
{
    std::jthread { test_v1 };

    std::jthread { test_v2 };

//  -------------------------

    assert(g_x1 == 2);

    assert(g_x2 == 2);
}

/////////////////////////////////////////////////////////////