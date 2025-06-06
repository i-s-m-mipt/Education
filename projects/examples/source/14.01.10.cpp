///////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <exception>
#include <future>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////

auto test_v1(int x) 
{ 
	return x;
}

///////////////////////////////////////////////////////////////////////////////////////////////

void test_v2()
{
	throw std::runtime_error("error");
}

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > auto invoke(F && f, Ts && ... xs)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (xs)...);
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto future = std::async(test_v1, 1);

//  -----------------------------------------------------------------

    assert(future.valid() == 1); assert(future.get() == 1);

    assert(future.valid() == 0);

//  -----------------------------------------------------------------

	try
	{
		std::async(test_v2).get();
	}
	catch(...) {}

//  -----------------------------------------------------------------

	assert(std::async(std::launch::async,    test_v1, 1).get() == 1);

	assert(std::async(std::launch::deferred, test_v1, 1).get() == 1);
	
//  -----------------------------------------------------------------

	assert(invoke(test_v1, 1).get() == 1);
}

///////////////////////////////////////////////////////////////////////////////////////////////