#include <cassert>
#include <iostream>
#include <string>

using namespace std::literals;

///////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

	Entity() : m_data_1(s_data_1), m_data_2(0), m_data_3(0) {}

//	Entity() : m_data_1(s_data_1), m_data_3(0), m_data_2(0) {} // error

//  ---------------------------------------------------------------------------

	Entity(const int & data_1, int data_2, int data_3) 
	: 
		m_data_1(data_1), 
		m_data_2(data_2),
		m_data_3(data_3)
	{}

	Entity(const int & data_1, int data_2) : Entity(data_1, data_2, 0) {}

//  ---------------------------------------------------------------------------

   ~Entity()
	{
		std::clog << "Entity::~Entity\n";
	}

//  ---------------------------------------------------------------------------

	auto data_1() const { return m_data_1; }
	auto data_2() const { return m_data_2; }
	auto data_3() const { return m_data_3; }

//  ---------------------------------------------------------------------------

	const auto & data_as_string() const
	{
	//	m_data_3 = 0; // error
				
		return m_cached_data.data_as_string(*this);
	}

//  ---------------------------------------------------------------------------

//	void set_data_3(int data) { m_data_3 = data; } // bad

	void set_data_3(int data) 
	{ 
		m_data_3 = data; 
		
		m_cached_data.set_invalid(); 
	}

//  ---------------------------------------------------------------------------

	static void test()
	{
		std::clog << "Entity::test : s_data_1 = " << s_data_1 << '\n';
		
//		std::clog << "Entity::test : m_data_3 = " << m_data_3 << '\n'; // error
	}

private:

	class Cached_Data 
	{ 
	public:

		auto data_as_string(const Entity & entity) -> const std::string &
		{
			if (m_is_invalid)
			{
				m_string = 
				(
					std::to_string(entity.m_data_1) + '/' +
					std::to_string(entity.m_data_2) + '/' +
					std::to_string(entity.m_data_3)
				);

				m_is_invalid = false;
			}
			
			return m_string;
		}

		void set_invalid()
		{
			m_is_invalid = true;
		}

	private:

		std::string m_string; bool m_is_invalid = true;
	};

//  ---------------------------------------------------------------------------

	const int & m_data_1 = 0;

	const int   m_data_2 = 0;

		  int   m_data_3 = 0;

//  ---------------------------------------------------------------------------

	mutable Cached_Data m_cached_data;

//  ---------------------------------------------------------------------------

	static inline       auto s_data_1 = 0;

	static        const auto s_data_2 = 0;

//	static        const auto s_data_3 = "aaaaa"s; // error

	static inline const auto s_data_4 = "aaaaa"s;
};

///////////////////////////////////////////////////////////////////////////////

int main()
{
	Entity entity_1;

//	entity_1.m_data_3 = 1; // error

	entity_1.set_data_3(1); 
	
	assert(entity_1.data_3() == 1);

	assert(entity_1.data_as_string() == "0/0/1");

//  ---------------------------------------------

	const Entity entity_2;

//  entity_2.set_data_3(1); // error

	assert(entity_2.data_3() == 0);

	assert(entity_2.data_as_string() == "0/0/0");

//  ---------------------------------------------

	Entity entity_3;

	Entity entity_4(1, 2, 3);
	
	Entity entity_5(1, 2);

//	Entity entity_6(); // warning

//  ---------------------------------------------

	entity_1.test(); Entity::test();
}