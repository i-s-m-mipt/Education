#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

//  ================================================================================================

class Entity
{
public:

	struct Nested
	{
		static void test(Entity & entity) 
		{
			entity.m_data = s_data_1;
		}
	};

//  ------------------------------------------------------------------------------------------------

//	Entity() { m_name = ""; m_data = 0; } // error

//	Entity() : m_name("") { m_data = 0; } // bad

//	Entity() : m_data(0), m_name("") {} // error

	Entity() : m_name(""), m_data(0) {}

	Entity(const std::string & name, int data) : m_name(name)
	{
		set_data(data);
	}

	Entity(const std::string & name) : Entity(name, 0) {}

   ~Entity()
	{
		std::clog << "Entity::~Entity\n";
	}

//  --------------------

	void test_v1() const
	{
		std::clog << "Entity::test_v1\n";

//		m_data = s_data_1; // error
	}

	void test_v2() const;

//  ---------------------

	auto data() const
	{ 
		return m_data; 
	}

//	void set_data(int data) { m_data = data; } // bad

	void set_data(int data)
	{
		m_data = data < s_data_1 ? s_data_1 : data; 
		
		m_data_cache.clear();
	}

//  -----------------------------------

	const auto & data_as_string() const
	{
//		m_data = s_data_1; // error

		if (m_data_cache.empty())
		{
			m_data_cache = std::to_string(m_data);
		}

		return m_data_cache;
	}

//  ---------------------

	static void test_v3()
	{
		std::clog << "Entity::test_v3\n";

//		m_data = s_data_1; // error
	}

//  --------------------------------------

	static inline       auto s_data_1 = 0;

	static        const auto s_data_2 = 0;

//	static        const auto s_data_3 = "aaaaa"s; // error

	static inline const auto s_data_4 = "aaaaa"s;

private:

	const std::string m_name; 

//  -------------------------
	
	int m_data = 0;

//  ---------------------------------

	mutable std::string m_data_cache;
};

//  ================================================================================================

void Entity::test_v2() const
{ 
	std::clog << "Entity::test_v2\n"; 
}

//  ================================================================================================

int main()
{
	Entity entity_1;

//	entity_1.m_data = 1; // error

	entity_1.test_v1();
	entity_1.test_v2();

	entity_1.set_data(1); 
	
	assert(entity_1.data() == 1);

//  ------------------------------------------------------------------------------------------------

	const Entity entity_2;

//  entity_2.set_data(1); // error

	assert(entity_2.data() == 0);

	assert(entity_2.data_as_string() == "0");

//  ------------------------------------------------------------------------------------------------

	Entity entity_3;

	Entity entity_4("entity_4", 1);
	
	Entity entity_5("entity_5");

//	Entity entity_6(); // error

	{
		Entity entity_7;
	}

//  ------------------------------------------------------------------------------------------------

	assert(Entity::s_data_1 == 0);

	Entity::test_v3();

	Entity::Nested::test(entity_1);
}