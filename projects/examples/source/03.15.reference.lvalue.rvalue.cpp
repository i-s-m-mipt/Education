#include <iostream>
#include <utility>

/////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	void test() const &  { std::cout << "Entity::test (1)\n"; }

	void test() const && { std::cout << "Entity::test (2)\n"; }
};

/////////////////////////////////////////////////////////////////////////////////

      auto & make_entity_v1() { static       Entity entity; return entity; }

const auto & make_entity_v2() { static const Entity entity; return entity; }

      auto   make_entity_v3() { return Entity(); }
	  
const auto   make_entity_v4() { return Entity(); }

/////////////////////////////////////////////////////////////////////////////////

void test(      Entity & ) { std::cout << "test (1)\n"; }

void test(const Entity & ) { std::cout << "test (2)\n"; }

void test(      Entity &&) { std::cout << "test (3)\n"; }

void test(const Entity &&) { std::cout << "test (4)\n"; }

/////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]]       Entity &  r_entity_01 = make_entity_v1();
//		[[maybe_unused]]       Entity &  r_entity_02 = make_entity_v2(); // error
//		[[maybe_unused]]       Entity &  r_entity_03 = make_entity_v3(); // error
//		[[maybe_unused]]       Entity &  r_entity_04 = make_entity_v4(); // error

		[[maybe_unused]] const Entity &  r_entity_05 = make_entity_v1();
		[[maybe_unused]] const Entity &  r_entity_06 = make_entity_v2();
		[[maybe_unused]] const Entity &  r_entity_07 = make_entity_v3();
		[[maybe_unused]] const Entity &  r_entity_08 = make_entity_v4();

//		[[maybe_unused]]       Entity && r_entity_09 = make_entity_v1(); // error
//		[[maybe_unused]]       Entity && r_entity_10 = make_entity_v2(); // error
		[[maybe_unused]]       Entity && r_entity_11 = make_entity_v3();
//		[[maybe_unused]]       Entity && r_entity_12 = make_entity_v4(); // error

//		[[maybe_unused]] const Entity && r_entity_13 = make_entity_v1(); // error
//		[[maybe_unused]] const Entity && r_entity_14 = make_entity_v2(); // error
		[[maybe_unused]] const Entity && r_entity_15 = make_entity_v3();
		[[maybe_unused]] const Entity && r_entity_16 = make_entity_v4();
	}

//  -----------------------------------------------------------------------------

	{
		auto x = 1.0;

//		[[maybe_unused]]       int &  r_x_1 = x; // error

		[[maybe_unused]] const int &  r_x_2 = x;

		[[maybe_unused]]       int && r_x_3 = x;

		[[maybe_unused]] const int && r_x_4 = x;
	}

//  -----------------------------------------------------------------------------

	{
		Entity entity_1;

		test(entity_1);

		const Entity entity_2; 
		
		test(entity_2);

		Entity entity_3;

		test(std::move(entity_3));

		test(Entity());
	}

//  -----------------------------------------------------------------------------

	{
		Entity entity; entity.test(); Entity().test();
	}
}