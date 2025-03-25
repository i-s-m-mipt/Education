struct Entity {};

////////////////////////////////////////////////////////////////////////////

      auto & make_entity_v1() { static       Entity entity; return entity; }

const auto & make_entity_v2() { static const Entity entity; return entity; }

      auto   make_entity_v3() { return Entity(); }
	  
const auto   make_entity_v4() { return Entity(); }

////////////////////////////////////////////////////////////////////////////

int main()
{
	[[maybe_unused]]       Entity &  entity_01 = make_entity_v1();

//	[[maybe_unused]]       Entity &  entity_02 = make_entity_v2(); // error

//	[[maybe_unused]]       Entity &  entity_03 = make_entity_v3(); // error

//	[[maybe_unused]]       Entity &  entity_04 = make_entity_v4(); // error

//  -----------------------------------------------------------------------

	[[maybe_unused]] const Entity &  entity_05 = make_entity_v1();
	
    [[maybe_unused]] const Entity &  entity_06 = make_entity_v2();
	
    [[maybe_unused]] const Entity &  entity_07 = make_entity_v3();
	
    [[maybe_unused]] const Entity &  entity_08 = make_entity_v4();

//  -----------------------------------------------------------------------

//	[[maybe_unused]]       Entity && entity_09 = make_entity_v1(); // error

//	[[maybe_unused]]       Entity && entity_10 = make_entity_v2(); // error
	
    [[maybe_unused]]       Entity && entity_11 = make_entity_v3();

//	[[maybe_unused]]       Entity && entity_12 = make_entity_v4(); // error

//  -----------------------------------------------------------------------

//	[[maybe_unused]] const Entity && entity_13 = make_entity_v1(); // error

//	[[maybe_unused]] const Entity && entity_14 = make_entity_v2(); // error

	[[maybe_unused]] const Entity && entity_15 = make_entity_v3();

	[[maybe_unused]] const Entity && entity_16 = make_entity_v4();
}