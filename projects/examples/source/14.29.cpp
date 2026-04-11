/////////////////////////////////////////////////////////////////////////////////////

// chapter : Parallelism

/////////////////////////////////////////////////////////////////////////////////////

// section : Synchronization

/////////////////////////////////////////////////////////////////////////////////////

// content : Thread Pools
//
// content : Library Boost.ASIO

/////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cmath>
#include <cstddef>
#include <format>
#include <future>
#include <iostream>
#include <syncstream>
#include <thread>
#include <utility>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////

#include <boost/asio.hpp>

/////////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
    auto id = std::this_thread::get_id();

    std::osyncstream(std::cout) << std::format("calculate : id = {}\n", id);

	auto x = 0.0;

	for (auto i = 0uz; i < size; ++i)
	{
		x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
	}

	return x;
}

/////////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
	return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
    boost::asio::thread_pool pool;

//  ---------------------------------------------------------------------------------

    std::vector < std::future < double > > futures(1 << 10);

//  ---------------------------------------------------------------------------------

    for (auto & future : futures)
    {
        auto lambda = [](){ return calculate(1 << 10); };

    //  -----------------------------------------------------------------------------

        future = boost::asio::post(pool, boost::asio::use_future(std::move(lambda)));
    }

//  ---------------------------------------------------------------------------------

    for (auto & future : futures)
    {
        assert(equal(future.get(), 1 << 10));
    }

//  ---------------------------------------------------------------------------------

    pool.join();
}

/////////////////////////////////////////////////////////////////////////////////////