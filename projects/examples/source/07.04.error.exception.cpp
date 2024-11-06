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

	explicit Error(int error) : m_error(error) {}

//  ------------------------------------------------------------------------------------------------

	const char * what() const noexcept override 
	{ 
		return "error"; 
	}

private:

	int m_error = 0;
};

//  ================================================================================================

[[noreturn]] void test_v1()
{
	std::clog << "test_v1 (1)\n";

	try
	{
		std::clog << "test_v1 (2)\n";
		
//		throw 1; // bad

		throw Error(1); //	support: std::runtime_error

//		throw std::system_error(std::make_error_code(std::errc::no_message), "error");

		std::clog << "test_v1 (3)\n";
	}
	catch (const Error & error)
	{
		std::cerr << "test_v1 : " << error.what() << '\n';

//		throw error; // bad

		throw;
	}

	std::clog << "test_v1 (4)\n";
}

//  ================================================================================================

void test_v2()
{
	std::clog << "test_v2 (1)\n";

	auto size = 5uz;

//	auto array = new int[size]{}; // bad

	std::vector < int > vector(size, 0);

	test_v1();

//	delete[] array; // bad

	std::clog << "test_v2 (2)\n";
}

//  ================================================================================================

void test_v3()
{
	std::clog << "test_v3 (1)\n";

	try
	{
		test_v2();
	}
	catch (const std::exception & exception)
	{
		std::cerr << "test_v2 : " << exception.what() << '\n';

		throw std::runtime_error("error");
	}

	std::clog << "test_v3 (2)\n";
}

//  ================================================================================================

class Entity
{
public:

	explicit Entity(int data) try : m_data(data)
	{
		std::clog << "Entity::Entity\n";

		throw std::runtime_error("error");
	}
	catch (...)
	{
		uninitialize();
	}

   ~Entity() noexcept
	{
		uninitialize();
	}

private:

	void uninitialize() const noexcept
	{ 
		try
		{
			std::clog << "Entity::uninitialize\n"; 
		}
		catch (...) {}
	}

public:

	void swap(Entity & other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

//  ------------------------------------------------------------------------------------------------

	auto data() const noexcept
	{
		return m_data;
	}

private:

	int m_data = 0;
};

//  ================================================================================================

template < typename T > void swap(T & x, T & y) noexcept
(
	std::is_nothrow_move_constructible_v < T > &&
	std::is_nothrow_move_assignable_v    < T > 
)
{
	auto z = std::move(y);
	     y = std::move(x);
		 x = std::move(z);
}

//  ================================================================================================

template < typename F, typename ... Ts > decltype(auto) invoke(F && f, Ts && ... args) noexcept
(
	noexcept(f(std::declval < Ts > ()...))
)
{
	return f(std::forward < Ts > (args)...);
}

//  ================================================================================================

int main()
{
	try
	{
		test_v3();

		return EXIT_SUCCESS;
	}
	catch (const std::runtime_error & exception)
	{
		std::cerr << "main : " << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (const std::exception & exception)
	{
		std::cerr << "main : " << exception.what() << '\n';

		return EXIT_FAILURE;
	}
	catch (...)
	{
		auto exception = std::current_exception();

		std::cerr << "main : unknown exception\n";

		return EXIT_FAILURE;
	}
}