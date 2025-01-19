#include <any>
#include <cassert>
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std::literals;

#include <boost/type_index.hpp>

/////////////////////////////////////////////////////////////////////////////////////

class Entity 
{
public:

	virtual ~Entity() = default;
};

/////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity {};

class Server : public Entity {};

/////////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		auto x = 1;

		static_assert(std::is_same_v < decltype( x ), int   > );

		static_assert(std::is_same_v < decltype((x)), int & > );

		auto & r_x_1 = x;

		[[maybe_unused]] decltype(auto) r_x_2 = r_x_1;
	}
	
//  ---------------------------------------------------------------------------------

	{
		Entity * entity = new Client(); 

//		assert( static_cast < Client * > (entity)); // bad

		assert(dynamic_cast < Client * > (entity)); // support: compiler-explorer.com

		delete entity;
	}

//  ---------------------------------------------------------------------------------

	{
		auto x = 1; auto & r_x = x; Entity * entity = new Client();

		std::cout << "main : typeid(      x) = " << typeid(      x).name() << '\n';

		std::cout << "main : typeid(    r_x) = " << typeid(    r_x).name() << '\n';

		std::cout << "main : typeid( entity) = " << typeid( entity).name() << '\n';

		std::cout << "main : typeid(*entity) = " << typeid(*entity).name() << '\n';

		delete entity;
	}

//  ---------------------------------------------------------------------------------

	{
		auto x = 1; auto & r_x = x; Entity * entity = new Client();

		using boost::typeindex::type_id_with_cvr;

		assert(type_id_with_cvr < decltype(      x) > ().pretty_name() ==    "int" );
	
		assert(type_id_with_cvr < decltype(    r_x) > ().pretty_name() ==    "int&");

		assert(type_id_with_cvr < decltype( entity) > ().pretty_name() == "Entity*");

		assert(type_id_with_cvr < decltype(*entity) > ().pretty_name() == "Entity&");

		delete entity;
	}

//  ---------------------------------------------------------------------------------

	{
		auto any = std::make_any < int > (1);

		assert(std::string(any.type().name()) == typeid(int).name());

		assert(std::any_cast < int > (any) == 1);
			
		any = "aaaaa"s;

		assert(std::string(any.type().name()) == typeid(std::string).name());

		assert(std::any_cast < std::string > (any) == "aaaaa");
	}
}