#include <iostream>

void print_v1() 
{
	std::cout << std::endl; 
}

template < typename T, typename ... Types >
void print_v1(T arg, Types ... args)
{
	std::cout << arg << ' ';

	print_v1(args...);
}

template < typename T >
void print_v2(T arg)
{
	std::cout << arg << ' ';
}

template < typename T, typename ... Types >
void print_v2(T arg, Types ... args)
{
	print_v2(arg);

	print_v2(args...);
}

struct Point
{
	explicit Point(double x, double y) : m_x(x), m_y(y) {}

	double m_x;
	double m_y;

}; // struct Point

template < typename T, typename ... Types >
auto make_object(Types ... args)
{
	std::cout << sizeof...(args) << std::endl;

	return new T(args...);
}

template < typename ... Types >
auto sum_v1(Types ... args)
{
	return (... + args); // note: (... + args) -> (((arg_1 + arg_2) + arg_3) + ...)
}

template < typename ... Types >
auto sum_v2(Types ... args)
{
	return (args + ...); // note: (args + ...) -> (... + (arg_n-2 + (arg_n-1 + arg_n)))
}

template < typename ... Types >
auto sum_v3(Types ... args)
{
	return (42 + ... + args); // note: (42 + ... + args) -> (((42 + arg_1) + arg_2) + ...)
}

template < typename ... Types >
auto sum_v4(Types ... args)
{
	return (args + ... + 42); // note: (args + ... + 42) -> (... + (arg_n-1 + (arg_n + 42)))
}

template < typename ... Types >
void f(Types ... args)
{
//	print_v1(args + 1...); // error: invalid syntax

	print_v1((args + 1)...); // note: or args + 1 ...
}

template < typename ... Types >
void g(Types ... args)
{
	print_v1(args + args...);
}

int main()
{
	print_v1('a', 42, 3.14);
	print_v2('a', 42, 3.14); std::cout << std::endl;

	[[maybe_unused]] auto ptr = make_object < Point > (1.0, 1.0);

	delete ptr;

	std::cout << sum_v1(1, 2, 3) << std::endl;
	std::cout << sum_v2(1, 2, 3) << std::endl;
	std::cout << sum_v3(1, 2, 3) << std::endl;
	std::cout << sum_v4(1, 2, 3) << std::endl;

	f(1, 2, 3);
	g(1, 2, 3);

	return 0;
}