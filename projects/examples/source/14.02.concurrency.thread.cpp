#include <cassert>
#include <chrono>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

using namespace std::literals;

#include <boost/noncopyable.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////

class Task
{
public:

	Task(int & x): m_data(x) {}

//  --------------------------------------

	void operator()() const
	{
		for (auto i = 0uz; i < 1'000; ++i) 
        {
            ++m_data;
        }
	}

private:

	int & m_data;
};

/////////////////////////////////////////////////////////////////////////////////////////////

void test(int & x, int y) 
{ 
    x = y; 
}

/////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{ 
public:

    void test() const
    { 
        std::cout << "Entity::test\n"; 
    } 
};

/////////////////////////////////////////////////////////////////////////////////////////////

class Thread : private boost::noncopyable
{
public:

	Thread(std::thread thread) : m_thread(std::move(thread))
	{
		if (!m_thread.joinable()) 
        {
            throw std::runtime_error("invalid thread");
        }
	}

   ~Thread()
	{
		m_thread.join();
	}

private:

	std::thread m_thread;
}; 

/////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    {
        std::thread thread([](){});

        thread.join();

//      std::thread([](){ std::this_thread::sleep_for(1s); }); // bad

        std::thread([](){ std::this_thread::sleep_for(1s); }).detach();

        [[maybe_unused]] auto x = 1;

//      std::thread(Task(x)).detach(); // bad
    }

//  -----------------------------------------------------------------------------------------

    {
        auto x = 1;

//      std::thread(test, x, 2).join(); // error

        std::thread(test, std::ref(x), 2).join(); assert(x == 2);

        Entity entity;

        Thread thread(std::thread(&Entity::test, &entity));
    }

//  -----------------------------------------------------------------------------------------

    {
        assert(std::thread::hardware_concurrency() != 0);

        std::vector < std::thread > threads;

        for (auto i = 0uz; i < std::thread::hardware_concurrency(); ++i)
        {
            threads.emplace_back([](){});
        }

        for (auto & thread : threads) 
        {
            thread.join();
        }
    }

//  -----------------------------------------------------------------------------------------

    {
        std::jthread jthread([](std::stop_token token)
        {
            std::stop_callback callback(token, [](){ std::cout << "jthread : callback\n"; });

            for (auto i = 0uz; i < 10; ++i)
            {
                std::cout << "jthread : i = " << i << '\n';

                std::this_thread::sleep_for(0.1s);

                if (token.stop_requested()) 
                {
                    return;
                }
            }
        });

        std::this_thread::sleep_for(0.5s);

        jthread.get_stop_source().request_stop();
    }
}