#include <exception>
#include <iostream>
#include <stdexcept>
#include <system_error>
#include <vector>

//  ================================================================================================

class Exception : public std::exception
{
public:

	Exception(int x) : m_data(x) {}

//  -------------------------------------------

	const char * what() const noexcept override 
	{ 
		return "exception"; 
	}

private:

	int m_data = 0;
};

//  ================================================================================================

[[noreturn]] void test_v1()
{
	std::cout << "test_v1 (1)\n";

	try
	{
		std::cout << "test_v1 (2)\n";
		
//		throw 1; // bad

		throw Exception(1); // support: std::runtime_error

//		throw std::system_error(std::make_error_code(std::errc::no_message), "error");

		std::cout << "test_v1 (3)\n";
	}
	catch (const Exception & exception)
	{
		std::cerr << "test_v1 : " << exception.what() << '\n';

//		throw exception; // bad

		throw;
	}

	std::cout << "test_v1 (4)\n";
}

//  ================================================================================================

void test_v2()
{
	std::cout << "test_v2 (1)\n";

//	auto array = new int[5]{ 1, 2, 3, 4, 5 }; // bad

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

	test_v1();

//	delete[] array; // bad

	std::cout << "test_v2 (2)\n";
}

//  ================================================================================================

void test_v3()
{
	std::cout << "test_v3 (1)\n";

	try
	{
		test_v2();
	}
	catch (const std::exception & exception)
	{
		std::cerr << "test_v3 : " << exception.what() << '\n';

		throw std::runtime_error("error");
	}

	std::cout << "test_v3 (2)\n";
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