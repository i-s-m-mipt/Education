#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity() = default;

	Entity(int x, int y) : m_data_1(x), m_data_2(y) {}

//	Entity(int x, int y) : m_data_2(x), m_data_1(y) {} // error

	Entity(int x) : Entity(x, 0) 
	{
//		m_data_2 = 1; // error
	}

   ~Entity() = default;

//  ---------------------------------------------------------------------

	auto data_1() const { return m_data_1; }

	auto data_2() const { return m_data_2; }

//  ---------------------------------------------------------------------

	const auto & data_as_string() const
	{
	//	m_data_1 = 1; // error
				
		return m_cache.data_as_string(*this);
	}

//  ---------------------------------------------------------------------

//	void set_data_1(int x) { m_data_1 = x; } // bad

	void set_data_1(int x) 
	{ 
		m_data_1 = x;
		
		m_cache.set_invalid();
	}

//  ---------------------------------------------------------------------

	static void test()
	{
		std::cout << "Entity::test\n";

	//	m_data_1 = 1; // error

		s_data_1 = 1;
	}

//  ---------------------------------------------------------------------

	static inline       auto s_data_1 = 0;

	static        const auto s_data_2 = 1;

//	static        const auto s_data_3 = "aaaaa"s; // error

	static inline const auto s_data_4 = "aaaaa"s;

private:

	class Cache 
	{ 
	public:

		auto data_as_string(const Entity & entity) -> const std::string &
		{
			if (m_is_invalid)
			{
				m_string = 
				(
					std::to_string(entity.m_data_1) + ' ' +
					
					std::to_string(entity.m_data_2)
				);

				m_is_invalid = 0;
			}
			
			return m_string;
		}

		void set_invalid()
		{
			m_string.clear();
			
			m_is_invalid = 1;
		}

	private:

		std::string m_string;
		
		bool m_is_invalid = 1;
	};

//  ---------------------------------------------------------------------

	mutable Cache m_cache;

//  ---------------------------------------------------------------------

		  int m_data_1 = 0;
	
	const int m_data_2 = 0;
};

///////////////////////////////////////////////////////////////////////////////////

int main()
{
	{
		Entity entity(1, 1);

//		entity.m_data_1 = 2; // error

		assert(entity.data_1() == 1);

		assert(entity.data_as_string() == "1 1");

		entity.set_data_1(2);
		
		assert(entity.data_1() == 2);
	}
	
//  ---------------------------------------------

	{
		const Entity entity(1, 1);
		
		assert(entity.data_1() == 1);

		assert(entity.data_as_string() == "1 1");

//  	entity.set_data_1(2); // error
	}

//  ---------------------------------------------

	{
		Entity entity_1;

//		Entity entity_2(); // error

		Entity entity_3(3, 3);
	
		Entity entity_4(4);
	}

//  ---------------------------------------------

	{
		Entity::s_data_1 = 1;

		Entity::test();

		assert(Entity::s_data_2 == 1);

		assert(Entity::s_data_4 == "aaaaa");
	}
}