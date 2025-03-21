#include <iostream>
#include <thread>
#include <vector>

////////////////////////////////////////////////////////////////////

void test(int x)
{
    std::cout << "test : x = " << x << '\n';
}

////////////////////////////////////////////////////////////////////

int main()
{
    std::vector < std::jthread > threads;

//  ----------------------------------------------------------------

    for (auto i = 0uz; i < std::thread::hardware_concurrency(); ++i)
    {
        threads.emplace_back(test, i + 1);
    }

//  ----------------------------------------------------------------

    std::ignore = std::this_thread::get_id();
}