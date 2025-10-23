////////////////////////////////////////////////////////////////////

#include <cassert>
#include <print>
#include <string>
#include <variant>

////////////////////////////////////////////////////////////////////

class Visitor
{
public :

    void operator()(int x) const
    {
        std::print("Visitor::operator() : x = {}\n", x);
    }

//  --------------------------------------------------------------

    void operator()(std::string const & string) const
    {
        std::print("Visitor::operator() : string = {}\n", string);
    }
};

////////////////////////////////////////////////////////////////////

class Entity
{ 
public : 

    Entity(int) {}

//  ------------------------------------

   ~Entity() 
    { 
		std::print("Entity::~Entity\n");
	} 
};

////////////////////////////////////////////////////////////////////

int main()
{
    std::variant < int, std::string > variant_1 = 1;

//  ----------------------------------------------------------------

//	std::variant < Entity, int > variant_2; // error

//  ----------------------------------------------------------------

    std::variant < std::monostate, Entity, int > variant_3;

//  ----------------------------------------------------------------

    static_assert(std::variant_size_v < decltype(variant_1) > == 2);

//  ----------------------------------------------------------------

    assert(std::holds_alternative < int > (variant_1));

//  ----------------------------------------------------------------

    assert(std::get < int > (variant_1) == 1);

//  ----------------------------------------------------------------

	(variant_3 = Entity(3)) = 3;

//  ----------------------------------------------------------------

    assert(std::holds_alternative < int > (variant_3));

//  ----------------------------------------------------------------

    std::visit(Visitor(), variant_1);
}

////////////////////////////////////////////////////////////////////