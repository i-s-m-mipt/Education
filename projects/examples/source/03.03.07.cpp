#include <tuple>
#include <utility>

//////////////////////////////////////

struct Entity {};

//////////////////////////////////////

auto test_v1() { return Entity(); }

auto test_v2() 
{ 
	Entity entity;
	
	return entity;

//  ----------------------------------

//	return std::move(entity); // error
}

//////////////////////////////////////

int main()
{
    std::ignore = test_v1();
	
	std::ignore = test_v2();
}