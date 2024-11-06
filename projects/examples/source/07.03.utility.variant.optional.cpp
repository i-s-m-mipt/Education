#include <cassert>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

//  ================================================================================================

auto test_v1(int x)
{
	std::variant < int, std::string > result(x);

	if (x != 1)
	{
		result = "aaaaa";
	}

	return result;
}

//  ================================================================================================

struct Entity_v1 { explicit Entity_v1(int) {} };

struct Entity_v2 
{ 
   ~Entity_v2() 
    { 
		std::clog << "Entity_v2::~Entity_v2\n"; 
	} 
};

struct Entity_v3 {};

//  ================================================================================================

auto test_v2(int x)
{
	return x == 1 ? std::optional < int > (x) : std::nullopt;
}

//  ================================================================================================

int main()
{
	std::variant < int, std::string > variant_1;

	variant_1 = test_v1(1);

	assert(variant_1.index() == 0);
	
	assert(std::get < int > (variant_1) == 1);

	if (auto object = std::get_if < int > (&variant_1); object)
	{
		assert(*object == 1);
	}

	assert(std::holds_alternative < int > (variant_1));

//  ------------------------------------------------------------------------------------------------

//	std::variant < Entity_v1, int > variant_2; // error

	std::variant < std::monostate, Entity_v1, int > variant_3;

//  ------------------------------------------------------------------------------------------------

	std::variant < int, std::string > variant_4(std::in_place_type < int > , 1);

	std::variant < int, std::string > variant_5(std::in_place_index < 0 > , 1);

//  ------------------------------------------------------------------------------------------------

	std::variant < Entity_v2, Entity_v3 > variant_6;

	variant_6 = Entity_v3();

//  ------------------------------------------------------------------------------------------------

	std::optional < int > optional_1;

	optional_1 = test_v2(1);

    assert(optional_1.has_value());

	assert(optional_1.value() == 1);

	assert(optional_1.value_or(2) == 1);

//  ------------------------------------------------------------------------------------------------

    auto optional_2 = std::make_optional(1);

	assert(*optional_2 == 1);

//  ------------------------------------------------------------------------------------------------

    std::optional < std::string > optional_3(std::in_place, 5, 'a');

    assert(optional_3->substr(1, 3) == "aaa");

//  ------------------------------------------------------------------------------------------------

  	boost::logic::tribool tribool = boost::logic::indeterminate;

  	if (tribool || !tribool)
    {
		std::cout << "tribool = true or false\n";
	}
 	else
	{
		std::cout << "tribool = indeterminate\n";
	}
}