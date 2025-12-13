//////////////////////////////////////////////////////////////

#include <exception>
#include <iostream>
#include <print>
#include <stdexcept>
#include <vector>

//////////////////////////////////////////////////////////////

class Exception : public std::exception
{
public :

	Exception(int x) : m_x(x) {}

//  -------------------------------------------

	char const * what() const noexcept override
	{
		return "exception";
	}

private :

	int m_x = 0;
};

//////////////////////////////////////////////////////////////

[[noreturn]] void test_v1()
{
	std::print("test_v1\n");

//	auto x = new auto(1); // error

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//	throw 1; // bad

	throw Exception(1);

//	delete x; // error

	std::print("test_v1\n");
}

//////////////////////////////////////////////////////////////

void test_v2()
{
	std::print("test_v2\n");

	try
	{
		test_v1();
	}
	catch (Exception const & exception)
	{
		std::cerr << "test_v2 : " << exception.what() << '\n';

	//	throw exception; // error

		throw;
	}

	std::print("test_v2\n");
}

//////////////////////////////////////////////////////////////

void test_v3()
{
	std::print("test_v3\n");

	try
	{
		test_v2();
	}
	catch (std::exception const & exception)
	{
		std::cerr << "test_v3 : " << exception.what() << '\n';

		throw std::runtime_error("error");
	}

	std::print("test_v3\n");
}

//////////////////////////////////////////////////////////////

int main()
{
	try
	{
		test_v3();
	}
	catch (std::exception const & exception)
	{
		std::cerr << "main : " << exception.what() << '\n';
	}
	catch (...)
	{
		std::cerr << "main : unknown exception\n";

	//  ------------------------------------------

		auto exception = std::current_exception();
	}
}

//////////////////////////////////////////////////////////////