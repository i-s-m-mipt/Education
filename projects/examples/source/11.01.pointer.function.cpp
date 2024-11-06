#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <utility>

//  ================================================================================================

void test_v1() 
{ 
	std::clog << "test_v1\n"; 
}

void test_v2(void(*function)()) 
{ 
	std::clog << "test_v2\n"; 
	
	function(); 
}

//  ================================================================================================

auto test_v3(int x, int y) 
{ 
	return x + y; 
}

template < typename F, typename ... Ts > decltype(auto) invoke(F && f, Ts && ... args)
{
	return f(std::forward < Ts > (args)...);
}

//  ================================================================================================

int main()
{
	static_assert(std::is_same_v < decltype( test_v1), void   () > );
	static_assert(std::is_same_v < decltype(&test_v1), void(*)() > );

	auto function = &test_v1;

	(*function)();
	  function ();

	test_v2(test_v1);

	assert(		invoke(test_v3, 1, 2) == 3);
	assert(std::invoke(test_v3, 1, 2) == 3);
}