#include <cassert>
#include <functional>
#include <thread>

/////////////////////////////////////////////

void test(int & x) 
{ 
    ++x;
}

/////////////////////////////////////////////

int main()
{
    auto x = 1;

//  -----------------------------------------

//  std::jthread(test,          x ); // error

    std::jthread(test, std::ref(x));

//  -----------------------------------------
        
    assert(x == 2);
}