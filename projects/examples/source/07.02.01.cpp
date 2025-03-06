#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

//////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////

[[noreturn]] void test_v1()
{
	std::cout << "test_v1\n";

//	auto ptr = new auto(1); // bad

	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//	throw 1; // bad

	throw Exception(1);
	
	std::cout << "test_v1\n";
}

//////////////////////////////////////////////////////////////

void test_v2()
{
	std::cout << "test_v2\n";

	try
	{
		test_v1();
	}
	catch (const Exception & exception)
	{
		std::cerr << "test_v2 : " << exception.what() << '\n';

//		throw exception; // bad

		throw;
	}

	std::cout << "test_v2\n";
}

//////////////////////////////////////////////////////////////

void test_v3()
{
	std::cout << "test_v3\n";

	try
	{
		test_v2();
	}
	catch (const std::exception & exception)
	{
		std::cerr << "test_v3 : " << exception.what() << '\n';

		throw std::runtime_error("error");
	}

	std::cout << "test_v3\n";
}

//////////////////////////////////////////////////////////////

int main()
{
	try
	{
		test_v3();
	}
	catch (const std::runtime_error & exception)
	{
		std::cerr << "main : " << exception.what() << '\n';
	}
	catch (const std::exception & exception)
	{
		std::cerr << "main : " << exception.what() << '\n';
	}
	catch (...)
	{
		auto exception = std::current_exception();

		std::cerr << "main : unknown exception\n";
	}
}