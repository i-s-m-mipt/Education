////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <syncstream>
#include <thread>

////////////////////////////////////////////////////////////////////////////

void test_v1()
{
    for (auto i = 0uz; i < 5; ++i)
    {
        std::cout << "test_v1 : id = " << std::this_thread::get_id() << '\n';
    }
}

////////////////////////////////////////////////////////////////////////////

void test_v2()
{
    for (auto i = 0uz; i < 5; ++i)
    {
        std::osyncstream stream(std::cout);

        stream   << "test_v2 : id = " << std::this_thread::get_id() << '\n';
    }
}

////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        std::jthread thread_1(test_v1);

        std::jthread thread_2(test_v1);
    }

//  -----------------------------------

    {
        std::jthread thread_1(test_v2);

        std::jthread thread_2(test_v2);
    }
}

////////////////////////////////////////////////////////////////////////////