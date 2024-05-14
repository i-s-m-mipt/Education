#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <type_traits>
#include <utility>
#include <vector>

//  ================================================================================================

class Error : public std::exception
{
public:

	explicit Error(int error_code) : m_error_code(error_code) {}

	[[nodiscard]] const char * what() const noexcept override { return "error"; } // demo

private:

	const int m_error_code;

}; // class Error : public std::exception

//  ================================================================================================

[[noreturn]] void h()
{
	std::cout << "h() called" << std::endl;

	try
	{
		// ...
		
//		throw 42; // bad

		throw Error(42); //	support: std::runtime_error

//		throw std::system_error(std::make_error_code(std::errc::no_message), "error");

		// ...
	}
	catch (const Error & error)
	{
		std::cerr << error.what() << '\n';

//		throw error; // bad

		throw;
	}

	std::cout << "h() exited" << std::endl;
}

//  ================================================================================================

void g()
{
	std::cout << "g() called" << std::endl;

	[[maybe_unused]] const std::size_t size = 5;

//	const auto array = new int[size]{}; // bad

	std::vector < int > vector(size, 0);

	h();

//	delete[] array; // bad

	std::cout << "g() exited" << std::endl;
}

//  ================================================================================================

void f()
{
	std::cout << "f() called" << std::endl;

	try
	{
		g();
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';

		throw std::runtime_error("error");
	}

	std::cout << "f() exited" << std::endl;
}

//  ================================================================================================

class C
{
public:

	explicit C(const std::string & data) try : m_data(data)
	{
		std::cout << "constructor" << std::endl;

		throw std::runtime_error("error");
	}
	catch (...)
	{
		std::cerr << "constructor exception\n";

		uninitialize();
	}

	[[nodiscard]] const std::string & data() const noexcept
	{
		return m_data;
	}

   ~C() noexcept
	{
		try { uninitialize(); } catch (...) { std::abort(); }
	}

	void uninitialize() { std::cout << "uninitialize" << std::endl; }

	void swap(C & other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

private:

	std::string m_data;

}; // class C

//  ================================================================================================

template < typename T > inline constexpr void swap(T & x, T & y) noexcept(

	std::is_nothrow_move_constructible_v < T > &&
	std::is_nothrow_move_assignable_v    < T > )
{
	auto z = std::move(y);
	     y = std::move(x);
		 x = std::move(z);
}

template < typename F, typename ... Ts > 

[[nodiscard]] inline constexpr decltype(auto) invoke(F && f, Ts && ... args) 

	noexcept(noexcept(f(std::declval < Ts > ()...)))
{
	return f(std::forward < Ts > (args)...); // support: std::invoke
}

//  ================================================================================================

int main()
{
	try
	{
		f();

		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error & exception)
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (...)
	{
		[[maybe_unused]] auto ptr = std::current_exception();

		std::cerr << "unknown exception\n";

		return EXIT_FAILURE;
	}
}