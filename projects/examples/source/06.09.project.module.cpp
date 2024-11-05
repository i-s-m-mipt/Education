module;

#include <utility>

export module demo;

export import demo.submodule;

//  =======================================================

export template 
< 
	typename F, typename ... Ts 
> 
[[nodiscard]] decltype(auto) invoke(F && f, Ts && ... args) 
{ 
	return f(std::forward < Ts > (args)...);
}

//  =======================================================

export namespace demo
{
	[[nodiscard]] int test_v2(int x); 

	[[nodiscard]] int test_v3(int x) 
	{ 
		return x; 
	}
}