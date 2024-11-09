#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

//  ================================================================================================

class Entity
{
private:

	struct Data_Cache 
	{ 
		void update(const Entity & entity)
		{
			data = std::to_string(entity.m_data);

			is_invalid = false;
		}

		std::string data; bool is_invalid = true;
	};

public:

//	Entity() { m_name = ""; m_data = 0; } // error

//	Entity() : m_name("") { m_data = 0; } // bad

//	Entity() : m_data(0), m_name("") {} // warning

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

//  -------------------------------------

	void test_v1() const
	{
		std::clog << "Entity::test_v1\n";

//		m_data = s_data; // error
	}

	void test_v2() const;

//  --------------------------------------------

	const auto & name() const { return m_name; }

		  auto   data() const { return m_data; }

//  -------------------------------------------------

//	void set_data(int data) { m_data = data; } // bad

	void set_data(int data)
	{
		m_data = data < s_data ? s_data : data; 
		
		m_data_cache.is_invalid = true;
	}

//  -----------------------------------

	const auto & data_as_string() const
	{
		if (m_data_cache.is_invalid)
		{
			m_data_cache.update(*this);
		}
		
		return m_data_cache.data;
	}

//  -----------------------------

	static void test_v3()
	{
		std::clog << "Entity::test_v3\n";

//		m_data = s_data; // error
	}

private:

	static inline auto s_data = 0;

//  ------------------------------

	const std::string m_name; 

//  -------------------------

	int m_data = 0;

//  --------------------------------

	mutable Data_Cache m_data_cache;
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

	entity_1.set_data(1); 
	
	assert(entity_1.data() == 1);

//  -----------------------------

	const Entity entity_2;

//  entity_2.set_data(1); // error

	assert(entity_2.data() == 0);

	assert(entity_2.data_as_string() == "0");

//  -----------------------------------------

	Entity entity_3;

	Entity entity_4("entity_4", 1);
	
	Entity entity_5("entity_5");

//	Entity entity_6(); // error

	{
		Entity entity_7;
	}

//  ------------------

	Entity::test_v3();
}