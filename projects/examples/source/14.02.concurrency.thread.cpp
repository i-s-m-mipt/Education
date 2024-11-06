#include <cassert>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

using namespace std::literals;

#include <boost/noncopyable.hpp>

//  ================================================================================================

class Task
{
public:

	explicit Task(int & data): m_data(data) {}

//  ------------------------------------------------------

	void operator()() const
	{
		for (auto i = 0uz; i < 1'000'000; ++i) 
        {
            ++m_data;
        }
	}

private:

	int & m_data;
};

//  ================================================================================================

void test(int & x, int y) 
{ 
    x = y; 
}

//  ================================================================================================

struct Entity 
{ 
    void test() const
    { 
        std::clog << "Entity::test\n"; 
    } 
};

//  ================================================================================================

class Scoped_Thread : private boost::noncopyable
{
public:

	explicit Scoped_Thread(std::thread thread) : m_thread(std::move(thread))
	{
		if (!m_thread.joinable()) 
        {
            throw std::runtime_error("invalid thread");
        }
	}

   ~Scoped_Thread()
	{
		m_thread.join();
	}

private:

	std::thread m_thread;
}; 

//  ================================================================================================

int main()
{
    std::thread thread([](){ std::cout << "Hello, world!" << std::endl; });

    std::cout << std::this_thread::get_id() << std::endl;
    std::cout <<           thread. get_id() << std::endl;

    thread.join();

//  std::thread([](){ std::this_thread::sleep_for(1s); }); // bad

//  ================================================================================================

    auto x = 1;

//  std::thread(Task(x)).detach(); // bad

//  std::thread(test, x, 2).join(); // bad

    std::thread(test, std::ref(x), 2).join();

    assert(x == 2);

//  ================================================================================================

    Entity entity;

    std::thread(&Entity::test, &entity).join();

//  ================================================================================================

    Scoped_Thread scoped_thread(std::thread(test, std::ref(x), 3));

//  ================================================================================================

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

//  ================================================================================================

    std::jthread jthread_1([](std::stop_token token)
    {
        std::stop_callback callback(token, []()
        {
            std::cout << "jthread_1::callback" << std::endl;
        });

        for (auto i = 0uz; i < 10; ++i)
        {
            std::cout << "jthread_1 : " << i << std::endl;

            std::this_thread::sleep_for(0.1s);
        }
    });

//  ================================================================================================

    std::jthread jthread_2([](std::stop_token token)
    {
        for (auto i = 0uz; i < 10; ++i)
        {
            std::cout << "jthread_2 : " << i << std::endl;

            std::this_thread::sleep_for(0.1s);

            if (token.stop_requested()) 
            {
                return;
            }
        }
    });

//  ================================================================================================

    std::this_thread::sleep_for(0.5s);

    jthread_1.get_stop_source().request_stop();
    jthread_2.get_stop_source().request_stop();
}