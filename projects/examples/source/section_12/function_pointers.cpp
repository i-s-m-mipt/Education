#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>

[[nodiscard]] auto f(int x) noexcept
{ 
	return (x + 1); 
}

[[nodiscard]] auto g(int (*f)(int), int x) // note: old-style function argument
{
	return f(x);
}

template < typename ... Types > [[nodiscard]] auto h(int (*f)(Types ...), Types ... args)
{
	return f(args...);
}

template < typename F, typename ... Types > [[nodiscard]] auto invoke(F && f, Types && ... args)
{
	return f(std::forward < Types > (args)...);
}

int main()
{
	using     f_t = int   (int) noexcept;
	using ptr_f_t = int(*)(int) noexcept; // note: popular type alias in old code

	static_assert(std::is_same_v < decltype( f),     f_t > );
	static_assert(std::is_same_v < decltype(&f), ptr_f_t > );

	auto ptr_f = &f; // note: auto -> int(*)(int), operator & is optional

	assert(      (*ptr_f)(0) == 1);
	assert(        ptr_f (0) == 1);
	assert(            f (0) == 1);
	assert(          g(f, 0) == 1);
	assert(          h(f, 0) == 1);
	assert(     invoke(f, 0) == 1);
	assert(std::invoke(f, 0) == 1); // note: generic caller for templates

	return 0;
}