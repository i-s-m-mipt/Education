////////////////////////////////////////////////

#include <iostream>
#include <print>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////

void test_v1(int x)
{
    for (auto i = 0uz; i < 5; ++i)
    {
        std::print("test_v1 : x = {}\n", x);
    }
}

////////////////////////////////////////////////

void test_v2(int x)
{
    for (auto i = 0uz; i < 5; ++i)
    {
        std::osyncstream stream(std::cout);

        stream << "test_v2 : x = " << x << '\n';
    }
}

////////////////////////////////////////////////

int main()
{
    {
        std::jthread jthread_1(test_v1, 1);

        std::jthread jthread_2(test_v1, 2);
    }

//  ---------------------------------------

    {
        std::jthread jthread_1(test_v2, 1);

        std::jthread jthread_2(test_v2, 2);
    }
}

////////////////////////////////////////////////