#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

/////////////////////////////////////////////////////////////////////////

void test_v1(std::shared_ptr < int > , int) 
{
	std::cout << "test_v1\n";
}

/////////////////////////////////////////////////////////////////////////

[[noreturn]] int test_v2() 
{
	throw std::runtime_error("error");
}

/////////////////////////////////////////////////////////////////////////

int main()
{
	try
	{
	//  test_v1(std::shared_ptr < int > (new auto(1)), test_v2()); // bad
	}
	catch (...) {}

//  ---------------------------------------------------------------------

	auto x = std::make_shared < int > (1);

//  ---------------------------------------------------------------------

	try
	{
		test_v1(std::make_shared < int > (1), test_v2());
	}
	catch (...) {}
}