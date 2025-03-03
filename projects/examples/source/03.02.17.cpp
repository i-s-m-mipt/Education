#include <any>
#include <cassert>
#include <string>
#include <typeinfo>

using namespace std::literals;

/////////////////////////////////////////////////////////////////////////

int main()
{
	auto any = std::make_any < int > (1);

//  ---------------------------------------------------------------------

	assert(std::string(any.type().name()) == typeid(int).name());

	assert(std::any_cast < int > (any) == 1);

//  ---------------------------------------------------------------------
			
	any = "aaaaa"s;

//  ---------------------------------------------------------------------

	assert(std::string(any.type().name()) == typeid(std::string).name());

	assert(std::any_cast < std::string > (any) == "aaaaa");
}