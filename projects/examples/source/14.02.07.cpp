///////////////////////////////////////////////////////////////////

#include <iostream>
#include <syncstream>
#include <thread>

///////////////////////////////////////////////////////////////////

void test_v1(int x)
{
    for (auto i = 0uz; i < 5; ++i)
    {
        std::cout << "test_v1 : x = " << x << " i = " << i << '\n';
    }
}

///////////////////////////////////////////////////////////////////

void test_v2(int x)
{
    std::osyncstream stream(std::cout);

    for (auto i = 0uz; i < 5; ++i)
    {
        stream << "test_v2 : x = " << x << " i = " << i << '\n';
    }
}

///////////////////////////////////////////////////////////////////

int main()
{
    {
        std::jthread thread_1(test_v1, 1);

        std::jthread thread_2(test_v1, 2);
    }

//  --------------------------------------

    std::cout << '\n';

//  --------------------------------------

    {
        std::jthread thread_1(test_v2, 1);

        std::jthread thread_2(test_v2, 2);
    }
}

///////////////////////////////////////////////////////////////////