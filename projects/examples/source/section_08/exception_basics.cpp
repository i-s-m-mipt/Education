#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <type_traits>
#include <utility>

class Error : public std::exception // good: inherited from std::exception
{
public:

	explicit Error(int error_code) : m_error_code(error_code) {}

	[[nodiscard]] const char * what() const override { return "error"; }

private:

	int m_error_code;

}; // class Error : public std::exception

[[noreturn]] void h() // note: inconvinient control flow return
{
	std::cout << "h() called" << std::endl;

	try
	{
		// note: some actions here before throwing an exception
		
//		throw 42; // bad: possible, but not good in exceptions

		throw Error(42); // note: user-defined exception

//		throw std::runtime_error("error"); // note: standard exception

//		throw std::system_error(std::make_error_code(std::errc::illegal_byte_sequence), "error");

		// note: actions are skipped after throwing an exception
	}
	catch (const Error & error) // note: only one exception is handled
	{
		std::cerr << error.what() << '\n';

//		throw error; // bad: copy-initialized copy

		throw; // good: rethrow the same exception, polymorphic type saved
	}

//	std::cout << "h() exited" << std::endl; // warning: unreachable code
}

void g()
{
	std::cout << "g() called" << std::endl;

//	auto a = new int[10]{}; // bad: consider RAII wrapper

	h();

//	delete[] a; // bad: possible memory leak in case of exceptions

//	std::cout << "g() exited" << std::endl; // warning: unreachable code
}

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

		throw std::runtime_error("error"); // note: throw new exception

//		std::cerr << "f() exited in catch" << '\n'; // warning: unreachable code
	}

//	std::cout << "f() exited" << std::endl; // warning: unreachable code
}

class C
{
public:

	explicit C(const std::string & data) try : m_data(data) // note: function try block
	{
		std::cout << "constructor" << std::endl;

		throw std::runtime_error("error");
	}
	catch (...) // note: destructor will not be called, but m_data will be destroyed
	{
		std::cerr << "constructor exception\n";

		uninitialize(); // note: mandatory call, prefer RAII wrappers instead
	}

	[[nodiscard]] const auto & data() const noexcept // good: primitive noexcept getter
	{
		return m_data;
	}

	~C() noexcept // good: exceptions do not leave the destructor
	{
		try
		{
			uninitialize();
		}
		catch (...) // good: catch all exceptions in destructor
		{
			std::cerr << "bad destructor\n";

			std::abort(); // note: abnormal termination
		}
	}

	void uninitialize() { std::cout << "uninitialize" << std::endl; }

	void swap(C & other) noexcept // good: noexcept swap function
	{
		std::swap(m_data, other.m_data);
	}

private:

	std::string m_data;

}; // class C

template < typename T >
void swap(T & a, T & b) noexcept(
	std::is_nothrow_move_constructible_v < T > &&
	std::is_nothrow_move_assignable_v    < T > ) // note: conditionally noexcept
{
	auto c = std::move(b);
	     b = std::move(a);
		 a = std::move(c);
}

template < typename F, typename T > auto invoke(F f, T x) noexcept(noexcept(f(std::declval < T > ())))
{
	return f(x);
}

int main()
{
	try
	{
		f();

		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error & exception) // note: specified catch handler
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (const std::exception & exception) // note: generalized catch handler
	{
		std::cerr << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (...) // good: catch all exceptions at last in main
	{
		[[maybe_unused]] auto ptr = std::current_exception(); // note: possible in catch (...)

		std::cerr << "unknown exception\n";

		return EXIT_FAILURE;
	}
}