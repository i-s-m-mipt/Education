#include <cassert>
#include <future>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename F, typename ... Ts > auto async_invoke(F && f, Ts && ... xs)
{
	return std::async(std::launch::async, std::forward < F > (f), std::forward < Ts > (xs)...);
}

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto lambda = [](auto x){ return x; };

//  ----------------------------------------------------------------

	assert(std::async(std::launch::async,    lambda, 1).get() == 1);

	assert(std::async(std::launch::deferred, lambda, 1).get() == 1);

//  ----------------------------------------------------------------

	assert(async_invoke(lambda, 1).get() == 1);
}