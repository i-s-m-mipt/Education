#include <exception>
#include <memory>
#include <stdexcept>

/////////////////////////////////////////////////////////////////////

void test_v1(std::shared_ptr < int > , int) {}

/////////////////////////////////////////////////////////////////////

[[noreturn]] int test_v2() 
{
	throw std::runtime_error("error");
}

/////////////////////////////////////////////////////////////////////

int main()
{
//  test_v1(std::shared_ptr < int > (new auto(1)), test_v2()); // bad

//  -----------------------------------------------------------------

	auto ptr = std::make_shared < int > (1);

//  -----------------------------------------------------------------

	try
	{
		test_v1(std::make_shared < int > (1), test_v2());
	}
	catch (...) {}
}