/////////////////////////////////////////

#include <chrono>
#include <iostream>
#include <thread>

/////////////////////////////////////////

using namespace std::literals;

/////////////////////////////////////////

void test()
{
    std::cout << "test\n";
}

/////////////////////////////////////////

class Task
{
public :

	Task(int & x) : m_x(x) {}

//  ------------------------------------

	void operator()() const
	{
		std::this_thread::sleep_for(5s);
        
        ++m_x;
	}

private :

	int & m_x;
};

/////////////////////////////////////////

int main()
{
    std::thread thread(test);

//  -------------------------------------

    thread.detach();

//  -------------------------------------

    [[maybe_unused]] auto x = 1;

//  -------------------------------------

//  std::thread(Task(x)).detach(); // bad
}

/////////////////////////////////////////