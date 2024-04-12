#include <iostream>

// =================================================================================================

void print_v1() 
{
	std::cout << std::endl; 
}

template < typename T, typename ... Ts > inline void print_v1(T arg, Ts ... args)
{
	std::cout << arg << ' '; print_v1(args...);
}

template < typename T > inline void print_v2(T arg)
{
	std::cout << arg << ' ';
}

template < typename T, typename ... Ts > inline void print_v2(T arg, Ts ... args)
{
	print_v2(arg);

	print_v2(args...);
}

// =================================================================================================

class Point
{
public:

	explicit Point(double x, double y) : m_x(x), m_y(y) {}

private:

	double m_x;
	double m_y;

}; // class Point

// =================================================================================================

template < typename T, typename ... Ts > [[nodiscard]] inline T * make_object(Ts ... args)
{
	std::cout << sizeof...(args) << std::endl;

	return new T(args...);
}

// =================================================================================================

template < typename ... Ts > [[nodiscard]] inline auto sum_v1(Ts ... args)
{
	return (... + args); // note: (... + args) -> (((arg_1 + arg_2) + arg_3) + ...)
}

template < typename ... Ts > [[nodiscard]] inline auto sum_v2(Ts ... args)
{
	return (args + ...); // note: (args + ...) -> (... + (arg_n-2 + (arg_n-1 + arg_n)))
}

template < typename ... Ts > [[nodiscard]] inline auto sum_v3(Ts ... args)
{
	return (42 + ... + args); // note: (42 + ... + args) -> (((42 + arg_1) + arg_2) + ...)
}

template < typename ... Ts > [[nodiscard]] inline auto sum_v4(Ts ... args)
{
	return (args + ... + 42); // note: (args + ... + 42) -> (... + (arg_n-1 + (arg_n + 42)))
}

// =================================================================================================

template < typename ... Ts > inline void f(Ts ... args)
{
//	print_v1(args + 42...); // error: invalid syntax

	print_v1((args + 42)...); // note: or args + 42 ...
}

template < typename ... Ts > inline void g(Ts ... args)
{
	print_v1(args + args...);
}

// =================================================================================================

int main()
{
	print_v1('a', 42, 3.14);
	print_v2('a', 42, 3.14); std::cout << std::endl;

	delete make_object < Point > (1.0, 1.0);

	std::cout << sum_v1(1, 2, 3) << std::endl;
	std::cout << sum_v2(1, 2, 3) << std::endl;
	std::cout << sum_v3(1, 2, 3) << std::endl;
	std::cout << sum_v4(1, 2, 3) << std::endl;

	f(1, 2, 3);
	g(1, 2, 3);

	return 0;
}