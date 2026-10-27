//////////////////////////////////////////////////////////////////////////

// chapter : Language Core Basics

//////////////////////////////////////////////////////////////////////////

// content : Inline Functions
//
// content : Function Specifier inline
//
// content : Attributes [[always_inline]] and [[noinline]]
//
// content : Attributes [[hot]] and [[cold]]
//
// content : As-If Rule
//
// content : Special Memory
//
// content : Type Qualifier volatile

//////////////////////////////////////////////////////////////////////////

#include <cassert>

//////////////////////////////////////////////////////////////////////////

inline auto test_v1(int x, int y)
{
    return x + y;
}

//////////////////////////////////////////////////////////////////////////

[[gnu::always_inline, gnu::hot]] inline auto test_v2(int x, int y)
{
    return x + y;
}

//////////////////////////////////////////////////////////////////////////

[[gnu::noinline, gnu::cold]] auto test_v3(int x, int y)
{
    return x + y;
}

//////////////////////////////////////////////////////////////////////////

int main()
{
    auto volatile x = 1, y = 2;

//  ----------------------------------------------------------------------

    assert(test_v1(x, y) == 3); // support : https://compiler-explorer.com

    assert(test_v2(x, y) == 3); // support : https://compiler-explorer.com

    assert(test_v3(x, y) == 3); // support : https://compiler-explorer.com

    assert(test_v1(1, 2) == 3); // support : https://compiler-explorer.com

    assert(test_v2(1, 2) == 3); // support : https://compiler-explorer.com

    assert(test_v3(1, 2) == 3); // support : https://compiler-explorer.com
}

//////////////////////////////////////////////////////////////////////////