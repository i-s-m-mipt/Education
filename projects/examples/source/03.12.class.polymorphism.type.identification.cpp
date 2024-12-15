#include <any>
#include <cassert>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std::literals;

#include <boost/type_index.hpp>

//  ================================================================================================

class Entity 
{
public:

	virtual ~Entity() = default;
};

class Client : public Entity {};
class Server : public Entity {};

//  ================================================================================================

int main()
{
	[[maybe_unused]] auto x = 1; 
	
	[[maybe_unused]] auto & r_x = x;

	[[maybe_unused]] auto y = r_x; 

	[[maybe_unused]] decltype(x) z = 1;

	[[maybe_unused]] decltype((y)) r_y_1 = y;

	[[maybe_unused]] decltype(auto) r_y_2 = r_y_1;

//  ------------------------------------------------------------------------------------------------

	Entity * entity = new Client(); 

//	assert( static_cast < Client * > (entity)); // bad

	assert(dynamic_cast < Client * > (entity)); // support: compiler-explorer.com

//  ------------------------------------------------------------------------------------------------

	std::cout << "typeid(      x).name() = " << typeid(      x).name() << '\n';
	std::cout << "typeid(    r_x).name() = " << typeid(    r_x).name() << '\n';
	std::cout << "typeid( entity).name() = " << typeid( entity).name() << '\n';
	std::cout << "typeid(*entity).name() = " << typeid(*entity).name() << '\n';

//  ------------------------------------------------------------------------------------------------

	using boost::typeindex::type_id_with_cvr;

	assert(type_id_with_cvr < decltype(      x) > ().pretty_name() ==    "int" );
	assert(type_id_with_cvr < decltype(    r_x) > ().pretty_name() ==    "int&");
	assert(type_id_with_cvr < decltype( entity) > ().pretty_name() == "Entity*");
	assert(type_id_with_cvr < decltype(*entity) > ().pretty_name() == "Entity&");

	delete entity;

//  ------------------------------------------------------------------------------------------------

	auto any = std::make_any < int > (1);

	assert(std::string(any.type().name()) == typeid(int).name());

	assert(std::any_cast < int > (any) == 1);
		
	any = "aaaaa"s;

	assert(std::string(any.type().name()) == typeid(std::string).name());

	assert(std::any_cast < std::string > (any) == "aaaaa");
}