#include <cassert>
#include <functional>
#include <iostream>

int f(int x) 
{ 
	return (x + 1); 
}

int g(int (*f)(int), int x) // note: old-style function transfer
{
	return f(x);
}

template < typename F, typename T > auto h(F && f, T && x)
{
	return f(std::forward < T > (x));
}

int main()
{
	int (*ptr_f)(int) = f; // note: function name is pointer to it 

	assert((*ptr_f)(0) == 1);
	assert(  ptr_f (0) == 1);
	assert(      f (0) == 1);

	assert(g(f, 0) == 1);
	assert(h(f, 0) == 1);

	assert(std::invoke(f, 0) == 1); // note: generic caller for templates

	return 0;
}