#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

//  ================================================================================================

void print_v1() {}

template < typename T, typename ... Ts > void print_v1(T arg, Ts ... args)
{
	std::cout << arg << ' '; 
	
	print_v1(args...); // support: cppinsights.io
}

//  ================================================================================================

template < typename T > void print_v2(T arg)
{
	std::cout << arg << ' ';
}

template < typename T, typename ... Ts > void print_v2(T arg, Ts ... args)
{
	print_v2(arg);

	print_v2(args...);
}

//  ================================================================================================

template < typename ... Ts > void print_v3(Ts ... args) 
{ 
	print_v1(args + args...); // support: cppinsights.io
}

//  ================================================================================================

template < typename ... Ts > [[nodiscard]] auto reduce_v1(Ts ... args)
{
	return (... + args); // support: cppinsights.io
}

template < typename ... Ts > [[nodiscard]] auto reduce_v2(Ts ... args)
{
	return (args + ...); // support: cppinsights.io
}

template < typename ... Ts > [[nodiscard]] auto reduce_v3(Ts ... args)
{
	return (0 + ... + args); // support: cppinsights.io
}

template < typename ... Ts > [[nodiscard]] auto reduce_v4(Ts ... args)
{
	return (args + ... + 0); // support: cppinsights.io
}

//  ================================================================================================

struct Entity 
{ 
	int data_1 = 0; 
	int data_2 = 0; 
};

//  ================================================================================================

template < typename T, typename ... Ts > [[nodiscard]] auto make_object(Ts ... args)
{
	std::cout << "sizeof...(args) = " << sizeof...(args) << '\n';

	return new T(args...);
}

//  ================================================================================================

int main()
{
	std::cout << "args = { "; print_v1(1, "aaaaa"s); std::cout << "}\n";
	std::cout << "args = { "; print_v2(1, "aaaaa"s); std::cout << "}\n";
	std::cout << "args = { "; print_v3(1, "aaaaa"s); std::cout << "}\n";

//  ------------------------------------------------------------------------------------------------

	assert(reduce_v1(1, 2) == 3);
	assert(reduce_v2(1, 2) == 3);
	assert(reduce_v3(1, 2) == 3);
	assert(reduce_v4(1, 2) == 3);

//  ------------------------------------------------------------------------------------------------

	delete make_object < Entity > (1, 1);
}