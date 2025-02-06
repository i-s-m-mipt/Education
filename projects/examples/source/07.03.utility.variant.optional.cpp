#include <cassert>
#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include <boost/logic/tribool.hpp>
#include <boost/logic/tribool_io.hpp>

/////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		std::variant < int, std::string > variant = 1;

		assert(variant.index() == 0);
	
		assert(std::get < int > (variant) == 1);

		if (auto ptr = std::get_if < int > (&variant); ptr)
		{
			assert(*ptr == 1);
		}

		assert(std::holds_alternative < int > (variant));
	}

//  ---------------------------------------------------------------------------------

	{
//		std::variant < Entity_v1, int > variant_1; // error

		std::variant < std::monostate, Entity_v1, int > variant_2;
	}

//  ---------------------------------------------------------------------------------

	{
		std::variant < int, std::string > variant_1(std::in_place_type  < int > , 1);

		std::variant < int, std::string > variant_2(std::in_place_index < 0   > , 2);
	}

//  ---------------------------------------------------------------------------------

	{
		std::variant < Entity_v2, Entity_v3 > variant;

		variant = Entity_v3();
	}

//  ---------------------------------------------------------------------------------

	{
		assert(std::make_optional(1).value_or(2) == 1);

    	assert(std::make_optional < std::string > (5, 'a')->contains("aaa"));
	}

//  ---------------------------------------------------------------------------------

	{
		boost::logic::tribool x = false, y = true, z = boost::logic::indeterminate;

		auto fv = boost::logic::tribool::false_value;

		auto tv = boost::logic::tribool::true_value;

		auto iv = boost::logic::tribool::indeterminate_value;

		assert((   ! x).value == tv && (   ! y).value == fv && (   ! z).value == iv);

		assert((x && x).value == fv && (x && y).value == fv && (x && z).value == fv);

		assert((y && x).value == fv && (y && y).value == tv && (y && z).value == iv);

		assert((z && x).value == fv && (z && y).value == iv && (z && z).value == iv);

		assert((x || x).value == fv && (x || y).value == tv && (x || z).value == iv);

		assert((y || x).value == tv && (y || y).value == tv && (y || z).value == tv);

		assert((z || x).value == iv && (z || y).value == tv && (z || z).value == iv);
	}

//  ---------------------------------------------------------------------------------

	{
		auto x = boost::logic::indeterminate;

		std::cout << "main : x = " << std::boolalpha << x << '\n';
	}
}