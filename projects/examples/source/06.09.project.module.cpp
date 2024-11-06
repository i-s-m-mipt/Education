module;

#include <utility>

export module demo;

export import demo.submodule;

//  =======================================================

export template < typename F, typename ... Ts > decltype(auto) invoke(F && f, Ts && ... args) 
{ 
	return f(std::forward < Ts > (args)...);
}

//  =======================================================

export namespace demo
{
	int test_v2(int x); 

	int test_v3(int x) 
	{ 
		return x; 
	}
}