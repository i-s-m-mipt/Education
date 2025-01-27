#include <iostream>
#include <utility>

//////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	void test() const &  { std::cout << "Entity::test (1)\n"; }

	void test() const && { std::cout << "Entity::test (2)\n"; }
};

//////////////////////////////////////////////////////////////////////////////////

      auto & make_entity_v1() { static       Entity entity; return entity; }

const auto & make_entity_v2() { static const Entity entity; return entity; }

      auto   make_entity_v3() { return Entity(); }
	  
const auto   make_entity_v4() { return Entity(); }

//////////////////////////////////////////////////////////////////////////////////

void test(      Entity & ) { std::cout << "test (1)\n"; }
void test(const Entity & ) { std::cout << "test (2)\n"; }
void test(      Entity &&) { std::cout << "test (3)\n"; }
void test(const Entity &&) { std::cout << "test (4)\n"; }

//////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		[[maybe_unused]]       Entity &  lr__entity_1 = make_entity_v1();
//		[[maybe_unused]]       Entity &  lr__entity_2 = make_entity_v2(); // error
//		[[maybe_unused]]       Entity &  lr__entity_3 = make_entity_v3(); // error
//		[[maybe_unused]]       Entity &  lr__entity_4 = make_entity_v4(); // error

		[[maybe_unused]] const Entity &  lr_centity_1 = make_entity_v1();
		[[maybe_unused]] const Entity &  lr_centity_2 = make_entity_v2();
		[[maybe_unused]] const Entity &  lr_centity_3 = make_entity_v3();
		[[maybe_unused]] const Entity &  lr_centity_4 = make_entity_v4();

//		[[maybe_unused]]       Entity && rr__entity_1 = make_entity_v1(); // error
//		[[maybe_unused]]       Entity && rr__entity_2 = make_entity_v2(); // error
		[[maybe_unused]]       Entity && rr__entity_3 = make_entity_v3();
//		[[maybe_unused]]       Entity && rr__entity_4 = make_entity_v4(); // error

//		[[maybe_unused]] const Entity && rr_centity_1 = make_entity_v1(); // error
//		[[maybe_unused]] const Entity && rr_centity_2 = make_entity_v2(); // error
		[[maybe_unused]] const Entity && rr_centity_3 = make_entity_v3();
		[[maybe_unused]] const Entity && rr_centity_4 = make_entity_v4();
	}

//  ------------------------------------------------------------------------------

	{
		auto x = 1.0;

//		[[maybe_unused]]       int &  lr__x = x; // error
		[[maybe_unused]] const int &  lr_cx = x;
		[[maybe_unused]]       int && rr__x = x;
		[[maybe_unused]] const int && rr_cx = x;
	}

//  ------------------------------------------------------------------------------

	{
		Entity entity_1;

		test(entity_1);

		const Entity entity_2; 
		
		test(entity_2);

		Entity entity_3;

		test(std::move(entity_3));
	}

//  ------------------------------------------------------------------------------

	{
		Entity entity; entity.test(); Entity().test();
	}
}