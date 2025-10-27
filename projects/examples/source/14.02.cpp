/////////////////////////////

#include <print>
#include <thread>

/////////////////////////////

void test()
{
    std::print("test\n");
}

/////////////////////////////

int main()
{
    std::thread thread(test);

//  -------------------------

    thread.join();
}

/////////////////////////////