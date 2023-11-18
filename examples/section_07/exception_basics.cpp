#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

class Error : public std::exception // good: inherited from std::exception
{
public:

	explicit Error(const std::string & message, int code) : 
		std::exception(message.c_str()), m_code(code) {}

	const char * what() const override { return "error"; }

private:

	int m_code;

}; // class Error : public std::exception

[[noreturn]] void h() // note: inconvinient control flow return
{
	std::cout << "h() called" << std::endl;

	try
	{
		throw Error("bad function", 42);
	}
	catch (const Error & error)
	{
		std::cout << error.what() << std::endl;

//		throw error; // bad: copy-initialized copy

		throw; // good: rethrow the same exception
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
		std::cout << exception.what() << std::endl;

		throw std::runtime_error("new exception"); // note: throw new exception

//		std::cout << "f() exited in catch" << std::endl; // warning: unreachable code
	}

//	std::cout << "f() exited" << std::endl; // warning: unreachable code
}

class C
{
public:

	explicit C(const std::string & data) try : m_data(data)
	{
		std::cout << "constructor" << std::endl;
	}
	catch (...) // note: destructor will not be called
	{
		std::cout << "constructor exception" << std::endl;

		throw; // good: rethrow the same exception
	}

	const auto & data() const noexcept // good: primitive noexcept getter
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

int main()
{
	try
	{
		f();

		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error & exception) // note: specified catch handler
	{
		std::cout << exception.what() << std::endl;

		return EXIT_FAILURE;
	}
	catch (const std::exception & exception) // note: generalized catch handler
	{
		std::cout << exception.what() << std::endl;

		return EXIT_FAILURE;
	}
	catch (...) // good: catch all exceptions at last in main
	{
		std::cout << "unknown exception" << std::endl;

		return EXIT_FAILURE;
	}
}