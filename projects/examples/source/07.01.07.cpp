#include <cassert>
#include <iostream>
#include <string>
#include <variant>

///////////////////////////////////////////////////////////////////////

class Entity_v1 { public: Entity_v1(int) {} };

class Entity_v2 
{ 
public:

   ~Entity_v2() 
    { 
		std::cout << "Entity_v2::~Entity_v2\n";
	} 
};

class Entity_v3 {};

///////////////////////////////////////////////////////////////////////

int main()
{
	std::variant < int, std::string > variant_1 = 1;

    std::variant < int, std::string > variant_2 = "aaaaa";

//  -------------------------------------------------------------------

    assert(std::holds_alternative < int > (variant_1));

    assert(std::get < int > (variant_1) == 1);

//  -------------------------------------------------------------------

    static_assert(std::variant_size_v < decltype(variant_1) > == 2);

//  -------------------------------------------------------------------

//	std::variant <                 Entity_v1, int > variant_3; // error

	std::variant < std::monostate, Entity_v1, int > variant_4;

//  -------------------------------------------------------------------

	std::variant < Entity_v2, Entity_v3 > variant_5;

	variant_5 = Entity_v3();
}