/////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include <string>
#include <variant>

/////////////////////////////////////////////////////////////////////////

class Visitor
{
public :

    void operator()(int x) const
    {
        std::cout << "Visitor::operator() : x = " << x << '\n';
    }

//  ---------------------------------------------------------------------

    void operator()(const std::string & string) const
    {
        std::cout << "Visitor::operator() : string = " << string << '\n';
    }
};

/////////////////////////////////////////////////////////////////////////

class Entity
{ 
public : 

    Entity(int) {}

//  -------------------------------------

   ~Entity() 
    { 
		std::cout << "Entity::~Entity\n";
	} 
};

/////////////////////////////////////////////////////////////////////////

int main()
{
    std::variant < int, std::string > variant_1 = 1;

//  ----------------------------------------------------------------

    static_assert(std::variant_size_v < decltype(variant_1) > == 2);

//  ----------------------------------------------------------------

    assert(std::get < int > (variant_1) == 1);

//  ----------------------------------------------------------------

    std::visit(Visitor(), variant_1);

//  ----------------------------------------------------------------

//	std::variant <                 Entity, int > variant_2; // error

	std::variant < std::monostate, Entity, int > variant_3;

//  ----------------------------------------------------------------

	variant_3 = Entity(3);

    variant_3 = 3;

//  ----------------------------------------------------------------

    assert(std::holds_alternative < Entity > (variant_3) == 0);
}

/////////////////////////////////////////////////////////////////////////