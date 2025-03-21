#include <iostream>
#include <thread>
#include <utility>

#include <boost/noncopyable.hpp>

///////////////////////////////////////////////////////////////

void test()
{
    std::cout << "test\n";
}

///////////////////////////////////////////////////////////////

class Thread : private boost::noncopyable
{
public :

	Thread(std::thread thread) : m_thread(std::move(thread)) {}

   ~Thread()
	{
        if (m_thread.joinable())
        {
            m_thread.join();
        }
	}

private :

	std::thread m_thread;
};

///////////////////////////////////////////////////////////////

int main()
{
    Thread thread { std::thread(test) };
}