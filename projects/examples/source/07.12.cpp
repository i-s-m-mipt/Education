//////////////////////////////////////////////////////////////

#include <print>
#include <stdexcept>
#include <type_traits>
#include <utility>

//////////////////////////////////////////////////////////////

class Entity
{
public :

	Entity(int x) try : m_x(x)
	{
		if (m_x < 0)
		{
			throw std::runtime_error("error");
		}
	}
	catch (...)
	{
		uninitialize();
	}

//  -----------------------------------------------

   ~Entity() noexcept
	{
	//	throw std::runtime_error("error"); // error

		uninitialize();
	}

//  -----------------------------------------------

	void swap(Entity & other) noexcept
	{
		std::swap(m_x, other.m_x);
	}

//  -----------------------------------------------

	auto get() const noexcept
	{
		return m_x;
	}

private :

	void uninitialize() const noexcept
	{ 
		try
		{
			std::print("Entity::uninitialize\n");
		}
		catch (...) {}
	}

//  -----------------------------------------------

	int m_x = 0;
};

//////////////////////////////////////////////////////////////

void test_v1()
{
	std::print("test_v1\n");
}

//////////////////////////////////////////////////////////////

void test_v2() 
{
    Entity entity_1(1); test_v1();

    Entity entity_2(2); test_v1();
}

//////////////////////////////////////////////////////////////

void test_v3() noexcept
{
    Entity entity_1(1); test_v1();

    Entity entity_2(2); test_v1();
}

//////////////////////////////////////////////////////////////

int main()
{
	static_assert(noexcept(std::declval < Entity > ().get()));

//  ----------------------------------------------------------

	Entity entity_1(1);
	
	Entity entity_2(2);

//  ----------------------------------------------------------

	entity_1.swap(entity_2);

//  ----------------------------------------------------------

	test_v2(); // support : compiler-explorer.com

    test_v3(); // support : compiler-explorer.com
}

//////////////////////////////////////////////////////////////