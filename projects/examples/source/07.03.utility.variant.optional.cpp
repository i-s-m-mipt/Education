#include <cassert>
#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

//  ================================================================================================

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

//  ================================================================================================

int main()
{
	std::variant < int, std::string > variant_1 = 1;

	assert(variant_1.index() == 0);
	
	assert(std::get < int > (variant_1) == 1);

	if (auto object = std::get_if < int > (&variant_1); object)
	{
		assert(*object == 1);
	}

	assert(std::holds_alternative < int > (variant_1));

//  -----------------------------------------------------------------------------

//	std::variant < Entity_v1, int > variant_2; // error

	std::variant < std::monostate, Entity_v1, int > variant_3;

//  -----------------------------------------------------------------------------

	std::variant < int, std::string > variant_4(std::in_place_type  < int > , 1);

	std::variant < int, std::string > variant_5(std::in_place_index < 0   > , 1);

//  -----------------------------------------------------------------------------

	std::variant < Entity_v2, Entity_v3 > variant_6;

	variant_6 = Entity_v3();

//  -----------------------------------------------------------------------------

	std::optional < int > optional_1 = 1;

    assert(optional_1.has_value());

	assert(optional_1.value() == 1);

	assert(optional_1.value_or(2) == 1);

//  -----------------------------------------------------------------------------

    auto optional_2 = std::make_optional(1);

	assert(*optional_2 == 1);

//  -----------------------------------------------------------------------------

    std::optional < std::string > optional_3(std::in_place, 5, 'a');

    assert(optional_3->substr(1, 3) == "aaa");

//  -----------------------------------------------------------------------------

  	boost::logic::tribool f = false, t = true, i = boost::logic::indeterminate;

//  -----------------------------------------------------------------------------

	std::cout << "main : i = " << std::boolalpha << i << '\n';

//  -----------------------------------------------------------------------------

	auto fv = boost::logic::tribool::false_value;

	auto tv = boost::logic::tribool::true_value;

	auto iv = boost::logic::tribool::indeterminate_value;

//  -----------------------------------------------------------------------------

  	assert((!f).value == tv && (!t).value == fv && (!i).value == iv);

//  -----------------------------------------------------------------------------

	assert((f && f).value == fv && (f && t).value == fv && (f && i).value == fv);
	assert((t && f).value == fv && (t && t).value == tv && (t && i).value == iv);
	assert((i && f).value == fv && (i && t).value == iv && (i && i).value == iv);

//  -----------------------------------------------------------------------------

	assert((f || f).value == fv && (f || t).value == tv && (f || i).value == iv);
	assert((t || f).value == tv && (t || t).value == tv && (t || i).value == tv);
	assert((i || f).value == iv && (i || t).value == tv && (i || i).value == iv);
}