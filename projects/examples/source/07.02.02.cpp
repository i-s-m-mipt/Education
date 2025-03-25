#include <cassert>
#include <exception>
#include <iostream>
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

   ~Entity() noexcept
	{
	//	throw std::runtime_error("error"); // error

		uninitialize();
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
			std::cout << "Entity::uninitialize\n";
		}
		catch (...) {}
	}

//  -----------------------------------------------

	int m_x = 0;
};

//////////////////////////////////////////////////////////////

template < typename T > void swap(T & x, T & y) noexcept
(
	std::is_nothrow_move_constructible_v < T > && 
	
	std::is_nothrow_move_assignable_v    < T >
)
{
	auto z = std::move(y);

	     y = std::move(x);

		 x = std::move(z);
}

//////////////////////////////////////////////////////////////

void test_v1() 
{
    Entity entity_1(1); std::cout << "test_v1\n";

    Entity entity_2(2); std::cout << "test_v1\n";
}

//////////////////////////////////////////////////////////////

void test_v2() noexcept
{
    Entity entity_1(1); std::cout << "test_v2\n";

    Entity entity_2(2); std::cout << "test_v1\n";
}

//////////////////////////////////////////////////////////////

int main()
{
	static_assert(noexcept(std::declval < Entity > ().get()));

//  ----------------------------------------------------------

	Entity entity_1(1);
	
	Entity entity_2(2);

//  ----------------------------------------------------------

	swap(entity_1, entity_2);

//  ----------------------------------------------------------

	test_v1(); // support : compiler-explorer.com

    test_v2(); // support : compiler-explorer.com
}