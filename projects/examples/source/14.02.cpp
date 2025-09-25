/////////////////////////////

#include <iostream>
#include <thread>

/////////////////////////////

void test()
{
    std::cout << "test\n";
}

/////////////////////////////

int main()
{
    std::thread thread(test);

//  -------------------------

    thread.join();
}

/////////////////////////////